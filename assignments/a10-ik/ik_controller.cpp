#include "ik_controller.h"
#include <cmath>
#include <iostream>
#include "atkmath/matrix3.h"
#include "atkmath/quaternion.h"

using namespace atk;
using namespace glm;
using namespace std;
using namespace atkmath;

bool IKController::solveIKAnalytic(Skeleton& skeleton, 
    int jointid, const vec3& goalPos, float epsilon) {
  if (jointid == -1) return true;

  Joint* ankle = skeleton.getByID(jointid);
  if (!ankle->getParent()) {
    std::cout << "Warning: solveIKAnalytic() needs joint "
      "with parent and grandparent\n";
    return false;
  }

  Joint* knee = ankle->getParent();
  if (!knee->getParent()) {
    std::cout << "Warning: solveIKAnalytic() needs joint "
      "with parent and grandparent\n";
    return false;
  }

  Joint* hip = knee->getParent();
  
  float l1 = length(hip->getGlobalTranslation() - knee->getGlobalTranslation());
  float l2 = length(knee->getGlobalTranslation() - ankle->getGlobalTranslation());
  float r1 = length(goalPos - hip->getGlobalTranslation());

  float angle = (r1*r1 - l1*l1 - l2*l2)/((-2) * l1 * l2);
  if (angle < -1) angle = -1;
  if (angle > 1) angle = 1;
  angle = acos(angle);
  float theta2z = angle - M_PI;

  vec3 limbDir = normalize(knee->getLocalTranslation());
  vec3 axis = cross(limbDir, vec3(0,0,-1));
  if (limbDir[1] < 0) axis = cross(limbDir, vec3(0,0,1));

  quat rot = angleAxis(theta2z, axis);
  knee->setLocalRotation(rot);
  vec3 r = ankle->getGlobalTranslation() - hip->getGlobalTranslation();
  vec3 e = goalPos - ankle->getGlobalTranslation();
  vec3 crossRE = cross(r,e);
  float theta = atan2(length(crossRE), dot(r,r) + dot(r,e));
  
  if (length(crossRE) < epsilon) crossRE = vec3(0,0,1);
  quat q = angleAxis(theta, normalize(crossRE));
  hip->setLocalRotation(inverse(hip->getParent()->getGlobalRotation()) * q * hip->getGlobalRotation());

  skeleton.fk();
  return true;
}

bool IKController::solveIKCCD(Skeleton& skeleton, int jointid, 
    const vec3& goalPos, const std::vector<Joint*>& chain, 
    float threshold, int maxIters, float nudgeFactor) {
  float epsilon = 0.000001;
  // There are no joints in the IK chain for manipulation
  if (chain.size() == 0) return true;
  int iter = 0;
  Joint* endEf = chain[0];
  vec3 p = endEf->getGlobalTranslation();
  while (length(goalPos - p) > threshold && iter < maxIters) {
    for(int i = 1; i < chain.size(); i++) {
      vec3 r = endEf->getGlobalTranslation() - chain[i]->getGlobalTranslation();
      vec3 e = goalPos - endEf->getGlobalTranslation();
      
      float theta = nudgeFactor * atan2(length(cross(r,e)), dot(r,r) + dot(r,e));

      vec3 axis = cross(r,e)/length(cross(r,e));
      quat parent = chain[i]->getParent()->getGlobalRotation();
      quat rot = angleAxis(theta, inverse(parent) * axis) * chain[i]->getLocalRotation();
      
      if (length(r) < epsilon) continue;
      if (length(e) < epsilon) continue;
      if (theta < epsilon) continue;
      if (length(axis) < epsilon) continue;
      if (length(rot) < epsilon) continue;
      if (length(parent) < epsilon) continue;

      chain[i]->setLocalRotation(rot);
      chain[i]->fk();
       
    }
    iter++;
    p = skeleton.getByID(jointid)->getGlobalTranslation();
  }
  return false;
}

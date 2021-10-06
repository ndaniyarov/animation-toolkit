#include "atkui/framework.h"
#include "atkmath/constants.h"
#include "atkmath/vector3.h"
#include "atkmath/matrix3.h"

using namespace glm;
using atkmath::Deg2Rad;
using atkmath::Rad2Deg;
using atkmath::Matrix3;
using atkmath::Vector3;

class Circles : public atkui::Framework
{
public:
   Circles() : atkui::Framework(atkui::Orthographic) {
   }
   struct particle {
    vec3 position;
    vec3 color;
    float dir;
    float theta;
    float radius;
    float angle;
  };

   virtual void setup() {
      k = 0;
      //number of circles
      n = 10;
      //10 degrees in radians
      thetaRate = 2*M_PI*(10.0f/360.0f);
      circleR = 10;
      dir = 1;
      for (int j = 1.0f; j <= n; j+=1.0f){
         theta = 0.0f;
         dir = -1.0 * dir;
         //evenly distributed circles
         r = (height()*j)/(2.0f*(n+1.0f));
         for (int i = 0; i < 36; i++){
            particle p;
            p.theta = theta;
            p.radius = r;
            p.position.x = r * (cos(p.theta)) + 0.5 * width();
            p.position.y = r * (sin(p.theta)) + 0.5 * height();
            p.position.z = 0;
            p.color = pallet[(j % pallet.size())];
            p.dir = dir;
            p.angle = j*Deg2Rad;
            particles.push_back(p);
            theta += thetaRate;
         }
      }
   }

   virtual void scene() {
      
      for (particle& p : particles) {
         //p.theta += p.dir * thetaRate * 0.5* dt();
         theta += thetaRate;
         //p.position.x = p.radius * (cos(p.theta)) + 0.5 * width();
         //p.position.y = p.radius * (sin(p.theta)) + 0.5 * height();
         //translate(vec3(p.position.x, p.position.y, 0.0f));
         setColor(p.color);
         //drawCube(p.position, vec3(width()/30.0f));
         //setColor(vec3(1,0,0));
         Vector3 euler(0.0001, 0, 0);
         Matrix3 rot;
         rot.fromEulerAnglesXYZ(euler*Deg2Rad);
         glm::mat4 rotm = rot.writeToMat4();
         Vector3 testXYZ = rot.toEulerAnglesXYZ();
         testXYZ = testXYZ * Rad2Deg;
         Vector3 anglesRad = euler* Deg2Rad;
         push();
         //translate(vec3(-3.5, 3.5, 0));
         rotate(anglesRad[0]+theta, vec3(1, 0, 0));
         rotate(anglesRad[1]+theta, vec3(0, 1, 0));
         rotate(anglesRad[2]+theta, vec3(0, 0, 1));
         
         // rotate(i+M_PI/6.0f, vec3(0,1,0));
         // rotate(i+M_PI/6.0f, vec3(0,0,1));
         //drawCone(p.position, circleR);
         drawTorus(p.position, 10.0);
         pop();
         k= k+1;
      }
   }
   private: 
      float n;
      float r;
      float theta;
      float thetaRate;
      float circleR;
      float dir;
      float k;
      std::vector<vec3> pallet = 
      {
         vec3(0,165,227)/255.0f,
         vec3(141,215,191)/255.0f,
         vec3(255,150,197)/255.0f,
         vec3(255,87,104)/255.0f,
         vec3(255,162,58)/255.0f
      };
      std::vector<particle> particles;

};

int main(int argc, char** argv)
{
   Circles viewer;
   viewer.run();
   return 0;
}


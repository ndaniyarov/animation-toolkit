#ifndef _interpolator_linear_H_
#define _interpolator_linear_H_

#include <string>
#include <vector>
#include "interpolator.h"

//--------------------------------
// Linear 
//--------------------------------

class InterpolatorLinear : public Interpolator
{
public:
    InterpolatorLinear() : Interpolator("Linear") {}
    virtual glm::vec3 interpolate(int segment, double u) const {
        glm::vec3 p1 = mCtrlPoints.at(segment);
        glm::vec3 p2 = mCtrlPoints.at(segment+1);
        glm::vec3 m = p1 * (1.0f - (float)u) + p2 * (float)u;
       return m;
    }

    virtual void computeControlPoints(const std::vector<glm::vec3>& keys) {
       if (keys.size() == 0 || keys.size() == 1) {
          mCtrlPoints.clear();
       }
       else {
          for (glm::vec3 key : keys) {
             mCtrlPoints.push_back(key);
          }
       }
    }
};

#endif

#ifndef _interpolator_catmullrom_
#define _interpolator_catmullrom_

#include <string>
#include <vector>
#include "interpolator.h"
#include <iostream>

//--------------------------------
// Catmull-Rom 
//--------------------------------

class InterpolatorCatmullRom : public Interpolator
{
public:
    InterpolatorCatmullRom() : Interpolator("Catmull-Rom") {}

    virtual glm::vec3 interpolate(int segment, double u) const {
       glm::vec3 p0 = mCtrlPoints.at(segment*3);
       glm::vec3 p1 = mCtrlPoints.at(segment*3 + 1);
       glm::vec3 p2 = mCtrlPoints.at(segment*3 + 2);
       glm::vec3 p3 = mCtrlPoints.at(segment*3 + 3);

       float i = (float)u;
       glm::vec3 final = (float)pow((1.0f-i),3.0f) * p0 + 3.0f*i*(float)(pow((1.0f-i),2.0f))*p1 + 
       (float)3.0f*(float)pow(i,2.0f)*(float)(1.0f-i)*p2 + (float)pow(i,3.0)*p3;
       return final;
    }

    virtual void computeControlPoints(const std::vector<glm::vec3>& keys) {
      if (keys.size() == 0 || keys.size() == 1) {
         mCtrlPoints.clear();
      }
      else {
         int a,b;
         for (int i = 0; i < keys.size(); i++) {
            mCtrlPoints.push_back(keys.at(i));
            //push last point and break
            if (i == keys.size()-1){
               break;
            }
            //clamp
            if (i-1 < 0){
               a = 0;
            }
            else {
               a = i-1;
            }
            if (i+2 >= keys.size()) {
               b = keys.size()-1;
            }
            else{
               b = i+2;
            }
            glm::vec3 b1 = keys.at(i) + 1.0f/6.0f * (keys.at(i+1) - keys.at(a));
            glm::vec3 b2 = keys.at(i+1) - 1.0f/6.0f * (keys.at(b) - keys.at(i));
            mCtrlPoints.push_back(b1);
            mCtrlPoints.push_back(b2);
            
         }
      }
   }
};

#endif

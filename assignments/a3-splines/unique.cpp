#include "atkui/framework.h"
#include "interpolator_linear.h"
#include "spline.h"
#include <string>
#include <iostream>
#include <algorithm>
using namespace glm;
class Unique : public atkui::Framework {
 public:
  Unique() : atkui::Framework(atkui::Orthographic) {
  }
   virtual void setup(){
     j = 0;
   }
   virtual void scene(){
      
      for (float i = 0; i <= width(); i = i+1.0f*width()/10.0f){
         keys.push_back(vec3(width()/2.0,height(),0));
         keys.push_back(vec3(i*j, height()/2.0f,0));
         keys.push_back(vec3(width()/2.0,0,0));
         if (i*j>width())
            j = 0;
         else 
            j=j+0.001;
      }
      InterpolatorLinear interp;
      interp.computeControlPoints(keys);
      
      for (int i = 0; i < interp.getNumControlPoints()-1; i++){
         setColor(vec3(0,0,1));
         drawSphere(interp.getControlPoint(i),10);
         drawLine(interp.getControlPoint(i),interp.getControlPoint(i+1));
         drawSphere(interp.getControlPoint(i+1),10);
      }

   }
   private:
      std::vector<vec3> keys;
      float j;
};
int main(int argc, char** argv) {
   Unique viewer;
   viewer.run();
   return 0;
}


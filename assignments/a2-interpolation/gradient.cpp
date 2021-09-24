#include <iostream>
#include "atkui/framework.h"
using namespace glm;

class Gradient : public atkui::Framework {
 public:
  Gradient() : atkui::Framework(atkui::Orthographic) {
  }

  virtual void scene() {
    for (float i = 0; i < n; i=i+1.0){
      for (float j = 0; j < n; j=j+1.0){
          vec3 cx0 = vec3(nw * (1.0f - ((float)j/n)) + ne * ((float)j/n));
          vec3 cx1 = vec3(sw * (1.0f - ((float)j/n)) + se * ((float)j/n));
          setColor(vec3(cx0 * (1 - i/n) + cx1 * (i/n)));
          drawCube(vec3(i*width()/n + width()/n/2.0f, j*height()/n + height()/n/2.0, 0), vec3(width()/n));
      }
    }
  }
  private:
    float n = 10.0;
    vec3 ne = vec3(1.0f,1.0f,0.0f);
    vec3 se = vec3(0.0f,1.0f,1.0f);
    vec3 nw = vec3(1.0f,0.0f,0.0f);
    vec3 sw = vec3(1.0f,0.0f,1.0f);
};

int main(int argc, char **argv) {
  Gradient viewer;
  viewer.run();
}
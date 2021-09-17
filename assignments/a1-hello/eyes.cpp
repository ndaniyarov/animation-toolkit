#include "atkui/framework.h"

using namespace glm;
class Eyes : public atkui::Framework
{
  public:
    Eyes() : atkui::Framework(atkui::Orthographic) {
    }

    virtual void setup() {
      theta = 0;
      thetaRate = 0.01;
    }

    virtual void scene() {
      setColor(vec3(1,1,1));
      drawSphere(vec3(0.25*width(), 0.5*height(),0), 150);
      drawSphere(vec3(0.75*width(), 0.5*height(),0), 150);

      theta += thetaRate * elapsedTime();
      float px = 125 + 50 * (cos(theta)) + 0.5* width();
      float py = 0.5 * height();
      setColor(vec3(0,0,0));
      drawSphere(vec3(px, py, +100), 20);
      float px2 = 10 + 50 * (cos(theta)) + 0.23* width();
      float py2 = 0.5 * height();
      drawSphere(vec3(px2, py2, +100), 20);
    }
  private: 
    float theta;
    float thetaRate;
};

int main(int argc, char** argv) {
  Eyes viewer;
  viewer.run();
  return 0;
}

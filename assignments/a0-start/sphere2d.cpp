#include "atkui/framework.h"

using glm::vec3;

class Sphere2D : public atkui::Framework {
 public:
  Sphere2D() : atkui::Framework(atkui::Orthographic) {
  }

  virtual void scene() {
    // colors are RGB triplets in range [0,1]
    // draw a sphere at center of screen
    double x = width() * 0.5;
    double y = height() * 0.5;
    double radius = 100; 
    double radius1 = 200;
    //red color 
    setColor(vec3(1,0,0));
    //draw red sphere
    drawSphere(vec3(x,y,-100), radius1);
    //green color
    setColor(vec3(0,1,0));
    //draw green sphere in front of red sphere
    drawSphere(vec3(x,y,0), radius);
  }
};

int main(int argc, char** argv)
{
  Sphere2D viewer;
  viewer.run();
  return 0;
}

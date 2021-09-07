#include "atkui/framework.h"

  using glm::vec3;

  class Sphere3D : public atkui::Framework {
  public:

  Sphere3D() : atkui::Framework(atkui::Perspective) {
  }

  vec3 position = vec3(0);
  vec3 direction = agl::randomUnitVector();
  vec3 velocity = vec3(100);
  bool spaceKeyUp = false;

  virtual void scene() {
    // colors are RGB triplets in range [0,1]
    setColor(vec3(0,1,0));

    // draw a sphere at center of the world
    float radius = 50.0;
    if (spaceKeyUp){
      position = position + (velocity * dt() * direction);
      drawSphere(position, radius);
    }
    else {
      drawSphere(vec3(0), radius);
    }
  }
  void keyUp(int key, int mods) {
    if (key == GLFW_KEY_SPACE){
      spaceKeyUp = true;
    }
    if (key == GLFW_KEY_R){
      direction = agl::randomUnitVector();
      position = vec3(0);
      spaceKeyUp = false;
    }
  }
};

int main(int argc, char** argv)
  {
    Sphere3D viewer;
    viewer.run();
    return 0;
  }
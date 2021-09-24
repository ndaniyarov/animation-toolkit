#include <iostream>
#include "atkui/framework.h"
using namespace glm;


class DrawCubic : public atkui::Framework
{
 public:
  DrawCubic() : atkui::Framework(atkui::Orthographic, 400, 400) {
  }

  virtual void scene()
  {
   if (rightClick){
      mouseMove(mousePosition().x, mousePosition().y);
      B1 = vec3(_mouseX, _mouseY, 0);
   }
   if (leftClick){
      mouseMove(mousePosition().x, mousePosition().y);
      B2 = vec3(_mouseX, _mouseY, 0);
   }
   setColor(vec3(0,0,1));
   drawSphere(B0, 10);
   drawSphere(B3, 10);

   setColor(vec3(1,1,0));
   drawSphere(B1, 10);
   drawSphere(B2, 10);
  
   for (float i = 0.0; i <=1; i = i + 0.001f){
      vec3 point = bernstain(B0, B1, B2, B3, i);
      setColor(vec3(1,0,0));
      drawSphere(point, 4);
   }
  }

  vec3 bernstain(vec3 b0, vec3 b1, vec3 b2, vec3 b3, float i){
    return (float)pow((1.0-i),3.0) * b0 + 3*i*(float)(pow((1.0-i),2.0))*b1 + (float)3.0*(float)pow(i,2.0)*(float)(1.0-i)*b2 + (float)pow(i,3.0)*b3;
  }
  void mouseMove(int x, int y) {
    _mouseX = x;
    _mouseY = 400 -y;
  }

  void mouseUp(int button, int mods){
    rightClick = false;
    leftClick = false;
  }

   virtual void mouseDown(int button, int mods){
    if (button == GLFW_MOUSE_BUTTON_RIGHT){
      rightClick = true;
      
    }
    if (button == GLFW_MOUSE_BUTTON_LEFT){
      leftClick = true;
    }
  }

 private:
  vec3 B0 = vec3(200,  50, 0);
  vec3 B1 = vec3(100, 200, 0);
  vec3 B2 = vec3(300, 200, 0);
  vec3 B3 = vec3(200, 350, 0);
  int _mouseX;
  int _mouseY;
  bool rightClick;
  bool leftClick;
};

int main(int argc, char **argv) {
  DrawCubic viewer;
  viewer.run();
}

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
    setColor(vec3(0,0,1));
    drawSphere(B0, 10);
    drawSphere(B3, 10);

    setColor(vec3(1,1,0));
    drawSphere(B1, 10);
    drawSphere(B2, 10);
    if (isBernstain){
      for (float i = 0.0; i <=1; i = i + 0.001f){
        vec3 point = bernstain(B0, B1, B2, B3, i);
        setColor(vec3(1,0,0));
        drawSphere(point, 4);
      }
    }
    else {
      setColor(vec3(0,0,1));
      for (float i = 0.0; i <=1; i = i + 0.001f){
        vec3 pt1 = casteljau(B0, B1, i);
        vec3 pt2 = casteljau(B1, B2, i);
        vec3 pt3 = casteljau(B2, B3, i);
        vec3 l2p1 = casteljau(pt1, pt2, i);
        vec3 l2p2 = casteljau(pt2, pt3, i);
        vec3 l3 = casteljau(l2p1, l2p2, i);
        drawSphere(l3, 4);
    }
  }
  }

  vec3 bernstain(vec3 b0, vec3 b1, vec3 b2, vec3 b3, float i){
    return (float)pow((1.0-i),3.0) * b0 + 3*i*(float)(pow((1.0-i),2.0))*b1 + (float)3.0*(float)pow(i,2.0)*(float)(1.0-i)*b2 + (float)pow(i,3.0)*b3;
  }

  vec3 casteljau(vec3 bi, vec3 bi1, float t){
    return bi*((float)1.0-t) + bi1*t;
  }

  void keyUp(int key, int mod) {
    if (key == GLFW_KEY_1) {
      isBernstain = true;
    }
    else if (key == GLFW_KEY_2) {
      isBernstain = false;
    }
  }

 private:
  vec3 B0 = vec3(100,  50, 0);
  vec3 B1 = vec3(150, 200, 0);
  vec3 B2 = vec3(250, 100, 0);
  vec3 B3 = vec3(300, 300, 0);
  bool isBernstain = false;
};

int main(int argc, char **argv) {
  DrawCubic viewer;
  viewer.run();
}

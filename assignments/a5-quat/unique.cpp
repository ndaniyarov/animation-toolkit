#include <iostream>
#include "atkui/framework.h"
#include "atkmath/matrix3.h"
#include "atkmath/quaternion.h"

using namespace glm;

class Gradient : public atkui::Framework {
 public:
  Gradient() : atkui::Framework(atkui::Orthographic) {
  }

  virtual void scene() {

    for (float i = 0; i < n; i=i+1.0){
      for (float j = 0; j < n; j=j+1.0){
         mouseMove(mousePosition().x, mousePosition().y);
         target = vec3(_mouseX, _mouseY, 0);
         setColor(vec3(1,0,0));
         drawSphere(target, 5);
         
         vec3 cx0 = vec3(nw * (1.0f - ((float)j/n)) + ne * ((float)j/n));
         vec3 cx1 = vec3(sw * (1.0f - ((float)j/n)) + se * ((float)j/n));
         setColor(vec3(cx0 * (1 - i/n) + cx1 * (i/n)));
         float x = i*width()/n + width()/n/2.0f;
         float y = j*height()/n + height()/n/2.0;
         float dist = sqrt(pow(x - target.x,2) + pow(y - target.y,2));
         temp = theta * pow(0.1,dt());
         if (dist < 100){
           push();
           translate(vec3(x,y,0));
           theta = atan2(target.y-y, target.x-x);
           rotate(theta, vec3(0,0,1));
           drawCube(vec3(0,0,0), vec3(20,1,0));
           pop();
         }
         else {
               push();
               translate(vec3(x,y,0));
               temp = theta * pow(0.1,dt());
               rotate(temp, vec3(0,0,1));
               drawCube(vec3(0,0,0), vec3(20,1,0));
               pop();
            //drawCube(vec3(x,y,0), vec3(20,1,0));

         }
      }
    }
  }
   void mouseMove(int x, int y) {
    _mouseX = x;
    _mouseY = height() - y;
  }

  void mouseUp(int button, int mods){
    rightClick = false;
  }

  void mouseDown(int button, int mods){
    rightClick = true;
  }
  private:
    float n = 30.0;
    vec3 ne = vec3(1.0f,1.0f,0.0f);
    vec3 se = vec3(0.0f,1.0f,1.0f);
    vec3 nw = vec3(1.0f,0.0f,0.0f);
    vec3 sw = vec3(1.0f,0.0f,1.0f);
    int _mouseX;
    int _mouseY;
    bool rightClick;
    vec3 target;
    float theta;
    float temp;
};

int main(int argc, char **argv) {
  Gradient viewer;
  viewer.run();
}
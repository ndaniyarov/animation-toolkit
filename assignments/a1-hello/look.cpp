#include "atkui/framework.h"

using namespace glm;

class Look : public atkui::Framework {
 public:
  Look() : atkui::Framework(atkui::Orthographic) {
  }

  virtual void setup() {
    _mouseX = width() * 0.5;
    _mouseY = height() * 0.5;

    theta = 0;
    px = 125 + 50 * (cos(theta)) + 0.5* width();
    py = 0.5 * height();
      
    px2 = 10 + 50 * (cos(theta)) + 0.23* width();
    py2 = 0.5 * height();
  }

  virtual void scene() {
    
    setColor(vec3(1,1,1));
    drawSphere(vec3(0.25*width(), 0.5*height(),0), 150);
    drawSphere(vec3(0.75*width(), 0.5*height(),0), 150);

    if (rightClick){
      mouseMove(mousePosition().x, mousePosition().y);
      target = vec3(_mouseX, _mouseY, 0);

      //find direction between origin and desired pnt
      dir1 = vec3(target.x - 0.75*width(), target.y - 0.5*height(), 0);
      dir2 = vec3(target.x - 0.25*width(), target.y - 0.5*height(), 0);
      //normalize
      dir1 = dir1 / std::sqrt(dir1.x*dir1.x + dir1.y*dir1.y);
      dir2 = dir2 / std::sqrt(dir2.x*dir2.x + dir2.y*dir2.y);
      //scale
      dir1 = 50.0f * dir1;
      dir2 = 50.0f * dir2;

      px = 0.75*width() + dir1.x;
      py = 0.5*height() + dir1.y;
      
      px2 = 0.25*width() + dir2.x;
      py2 = 0.5*height() + dir2.y;
    }
    setColor(vec3(1,0,0));
    drawSphere(target, 5);
    setColor(vec3(0,0,0));
    drawSphere(vec3(px, py, +100), 20);
    drawSphere(vec3(px2, py2, +100), 20);
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
  int _mouseX;
  int _mouseY;
  bool rightClick;
  vec3 target;
  float theta;
  float px, py, px2, py2;
  vec3 dir1, dir2;
};

int main(int argc, char** argv) {
  Look viewer;
  viewer.run();
  return 0;
}

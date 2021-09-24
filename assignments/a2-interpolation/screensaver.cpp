#include "atkui/framework.h"
using namespace glm;

class Screensaver : public atkui::Framework {
  struct Curve {
    vec3 b0, b1, b2, b3;
    vec3 color;
  };
 public:
  Screensaver() : atkui::Framework(atkui::Orthographic, 400, 400) {
  }

  void setup() {
    c1.b0 = randomNum(400);
    c1.b1  = randomNum(400);
    c1.b2  = randomNum(400);
    c1.b3  = randomNum(400);
    c1.color = randomColor();
    
    c2.b0 = randomNum(400);
    c2.b1 = randomNum(400);
    c2.b2 = randomNum(400);
    c2.b3 = randomNum(400);
    c2.color = randomColor();
    
    m.b0 = c1.b0;
    m.b1 = c1.b1;
    m.b2 = c1.b2;
    m.b3 = c1.b3;
    m.color = c1.color;

    a = 0;
  }

  void scene() {
    a=a+0.01;
    m.b0 = interpolation(m.b0,c2.b0,a);
    m.b1 = interpolation(m.b1,c2.b1,a);
    m.b2 = interpolation(m.b2,c2.b2,a);
    m.b3 = interpolation(m.b3,c2.b3,a);
    m.color = interpolation(m.color, c2.color, a);
        
    curves.push_back(m);
    if (curves.size() > 50){
      curves.pop_front();
    }
    for (Curve& c : curves){
      for (float j = 0; j <= 1; j= j+0.01){
        if (a > 0.3){
          a = 0;
          c1 = c;
          c2 = randomCurve();
        }
        vec3 newPosition = bernstain(c.b0,c.b1,c.b2,c.b3,j);
        setColor(c.color);
        drawSphere(newPosition, 1.0f);
      }
    }
  }

  vec3 interpolation(vec3 bi, vec3 bi1, float t){
    return vec3(bi * (1.0f-t) + bi1 * t);
  }
  vec3 bernstain(vec3 b0, vec3 b1, vec3 b2, vec3 b3, float i){
    return (float)pow((1.0-i),3.0) * b0 + 3*i*(float)(pow((1.0-i),2.0))*b1 + (float)3.0*(float)pow(i,2.0)*(float)(1.0-i)*b2 + (float)pow(i,3.0)*b3;
  }
  vec3 randomNum(int max){
    return vec3((float)(random()%max),(float)(random()%max), 0);
  }
  vec3 randomColor(){
    vec3 col;
    col = agl::randomUnitVector();
    return col;
  }
  Curve randomCurve(){
    Curve c;
    c.b0 = randomNum(400);
    c.b1  = randomNum(400);
    c.b2  = randomNum(400);
    c.b3  = randomNum(400);
    c.color = randomColor();
    return c;
  }
  private:
  Curve c1,c2,m;
  float a;
  std::list<Curve> curves;
};

int main(int argc, char** argv) {
  Screensaver viewer;
  viewer.run();
}


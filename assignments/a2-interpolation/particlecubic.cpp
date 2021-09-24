#include "atkui/framework.h"
using namespace glm;

class ParticleCubic : public atkui::Framework {
 public:
  ParticleCubic() : atkui::Framework(atkui::Orthographic, 400, 400) {
  }

  void setup() {
  }
  void scene() {
    for (float i = 0.0; i <=1; i = i + 0.001f){
      vec3 point = bernstain(B0, B1, B2, B3, i);
      setColor(vec3(1,1,0));
      drawSphere(point, 1);
    }
    setColor(vec3(1,0,0));
    cubicParticle(B0, B1, B2, B3);
  }
  vec3 bernstain(vec3 b0, vec3 b1, vec3 b2, vec3 b3, float i){
    return (float)pow((1.0-i),3.0) * b0 + 3*i*(float)(pow((1.0-i),2.0))*b1 + (float)3.0*(float)pow(i,2.0)*(float)(1.0-i)*b2 + (float)pow(i,3.0)*b3;
  }
  void cubicParticle(vec3 b0, vec3 b1, vec3 b2, vec3 b3) { 
    float a = fmod(elapsedTime()/5.0f,1);
    drawSphere(bernstain(B0, B1, B2, B3, a), 10);
  }
  private:
  vec3 B0 = vec3(100,  50, 0);
  vec3 B1 = vec3(150, 200, 0);
  vec3 B2 = vec3(250, 100, 0);
  vec3 B3 = vec3(300, 300, 0);
};

int main(int argc, char** argv) {
  ParticleCubic viewer;
  viewer.run();
}


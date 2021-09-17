#include "atkui/framework.h"

using namespace glm;

class Particles : public atkui::Framework
{
  struct particle {
    vec3 position;
    vec3 color;
    float velocity;
  };

 public:
  Particles() : atkui::Framework(atkui::Orthographic) {
  }

  double randomY(){
    return (float)rand()/(float)(RAND_MAX/height());
  }
  double randomX(){
    return (float)rand()/(float)(RAND_MAX/width());
  }

  virtual void setup() {
    vec3 baseColor = vec3(0.5,0.1, 1);
    for (int i = 0; i < 501; i++){
      particle p;
      p.position = vec3(randomX(), randomY(), (float)i);
      p.velocity = (float)rand()/(float)(RAND_MAX/200);
      p.color = baseColor + agl::randomUnitVector()/3.0f;
      particles.push_back(p);
    }
  }

  virtual void scene() {
    for (particle& p : particles){  
      if (p.position.x > width()){
        p.position.x = 0.0;
        p.position.y = randomY();
      }
      else if (p.position.y > height()){
        p.position.y = 0.0;
        p.position.x = randomX();
      }
      else {
        p.position += p.velocity * direction * dt();
      }
      setColor(p.color);
      drawSphere(p.position, radius);
    }
  }
  vec3 direction = vec3(1,1,0);
  float radius = 10.0;
  std::vector<particle> particles;
};

int main(int argc, char** argv) {
  Particles viewer;
  viewer.run();
  return 0;
}

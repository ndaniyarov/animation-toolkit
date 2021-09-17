#include "atkui/framework.h"

using namespace glm;

class Unique : public atkui::Framework {
 public:
  Unique() : atkui::Framework(atkui::Orthographic) {
  }
  struct particle {
    vec3 position;
    vec3 color;
    float velocity;
  };
  double randomX(){
    return (float)rand()/(float)(RAND_MAX/width());
  }
  double randomY(){
    return (float)rand()/(float)(RAND_MAX/height());
  }

  virtual void setup() {
    for (int i = 0; i < 200; i++){
      particle p;
      p.position = vec3(randomX(), randomY(), 600);
      p.velocity = (float)(rand()+100)/(float)(RAND_MAX/200);
      p.color = vec3(1,1,1);
      particles.push_back(p);
    }
  }

  virtual void scene() {
    setColor(vec3(.68, .85, .9));
    drawSphere(vec3(width()/2.0, height()/2.0, -50), 700);
    setColor(vec3(.83,.83,.83));
    drawSphere(vec3(width()/2.0, -100, 100), 600);
    setColor(vec3(1,1,1));
    drawSphere(vec3(width()/2.0, height()/2.0-100, 300), 150);
    drawSphere(vec3(width()/2.0, height()/2.0, 400), 100);
    setColor(vec3(0,0,0));

    theta += thetaRate * 10* dt();
    float px = 110 + 25 * (cos(theta)) + 0.3* width();
    float py = 0.5 * height();
    setColor(vec3(0,0,0));
    drawSphere(vec3(px, py, +500), 10);
    float px2 = 100 + 25 * (cos(theta)) + 0.28* width();
    float py2 = 0.5 * height();
    drawSphere(vec3(px2, py2, +500), 10);

    setColor(vec3(0.99,0.99,0.99));
    for (particle& p : particles) {
      if (p.position.y < 0){
        p.position.y = height();
        p.position.x = randomX();
      }
      else {
        p.position += p.velocity * direction * dt();
      }
      drawSphere(p.position, 10);
    }
  }
  vec3 direction = vec3(0,-1,0);
  float radius = 10.0;
  std::vector<particle> particles;
  float theta = 0.0;
  float thetaRate = 0.1;
};

int main(int argc, char** argv) {
  Unique viewer;
  viewer.run();
  return 0;
}


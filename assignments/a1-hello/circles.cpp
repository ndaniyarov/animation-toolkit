#include "atkui/framework.h"

using namespace glm;
class Circles : public atkui::Framework
{
public:
   Circles() : atkui::Framework(atkui::Orthographic) {
   }
   struct particle {
    vec3 position;
    vec3 color;
    float dir;
    float theta;
    float radius;
  };

   virtual void setup() {
      //number of circles
      n = 15;
      //10 degrees in radians
      thetaRate = 2*M_PI*(10.0f/360.0f);
      circleR = 10;
      dir = 1;
      for (int j = 1.0f; j <= n; j+=1.0f){
         theta = 0.0f;
         dir = -1.0 * dir;
         //evenly distributed circles
         r = (height()*j)/(2.0f*(n+1.0f));
         for (int i = 0; i < 36; i++){
            particle p;
            p.theta = theta;
            p.radius = r;
            p.position.x = r * (cos(p.theta)) + 0.5 * width();
            p.position.y = r * (sin(p.theta)) + 0.5 * height();
            p.position.z = 0;
            p.color = pallet[(j % pallet.size())];
            p.dir = dir;
            particles.push_back(p);
            theta += thetaRate;
         }
      }
   }

   virtual void scene() {
      for (particle& p : particles) {
         p.theta += p.dir * thetaRate * 0.5* dt();
         p.position.x = p.radius * (cos(p.theta)) + 0.5 * width();
         p.position.y = p.radius * (sin(p.theta)) + 0.5 * height();
         setColor(p.color);
         drawSphere(p.position, circleR);
      }
   }
   private: 
      float n;
      float r;
      float theta;
      float thetaRate;
      float circleR;
      float dir;
      std::vector<vec3> pallet = 
      {
         vec3(0,165,227)/255.0f,
         vec3(141,215,191)/255.0f,
         vec3(255,150,197)/255.0f,
         vec3(255,87,104)/255.0f,
         vec3(255,162,58)/255.0f
      };
      std::vector<particle> particles;

};

int main(int argc, char** argv)
{
   Circles viewer;
   viewer.run();
   return 0;
}

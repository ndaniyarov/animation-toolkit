#include <random>
#include <functional>
#include "atkui/framework.h"
#include "atk/toolkit.h"
#include "agl/renderer.h"
#include "devil.h"

using namespace atk;
using namespace glm;

class Thriller : public atkui::Framework
{
public:
   Thriller() : atkui::Framework(atkui::Perspective) {}
   virtual ~Thriller() {}

   virtual void setup() {
      BVHReader reader;
      reader.load("../motions/Warrok/WarrokThriller.bvh", _skeleton, _motion);

      vec3 position = vec3(0);
      vec3 baseColor = vec3(1,0, 0);
      float size = 1.0f;
      std::vector<vec3> positions;
      //todo later: jitter
      positions.push_back(vec3(100,0,0));
      positions.push_back(vec3(0,0,100));
      positions.push_back(vec3(-100, 0, 0));
      positions.push_back(vec3(0, 0, -100));
      positions.push_back(vec3(0, 0, 0));
      positions.push_back(vec3(-100, 0, 100));
      positions.push_back(vec3(-100, 0, -100));
      positions.push_back(vec3(100, 0, 100));
      positions.push_back(vec3(100, 0, -100));
      positions.push_back(vec3(-50, 0, 50));
      positions.push_back(vec3(50, 0, 50));
      positions.push_back(vec3(50, 0, -50));
      
      
      for (vec3& p : positions){
         //random size
         float random = ((float) rand()) / (float) RAND_MAX;
         float range = 0.9 - 0.2; 
         size = (random*range) + 0.2;
         _devil = Devil(p, baseColor + agl::randomUnitVector()/3.0f,size);
         devils.push_back(_devil);
      }
      
   }

   virtual void scene() {
      if (!_paused) _motion.update(_skeleton, elapsedTime());
      for (Devil& d : devils){
         d.draw(_skeleton, *this);
      }
   }

   virtual void keyUp(int key, int mods) {
      if (key == 'P') _paused = !_paused;
   }

protected:
   Motion _motion;
   Skeleton _skeleton;
   bool _paused = false;
   Devil _devil;
   std::vector<Devil> devils;
};

int main(int argc, char** argv) {
   Thriller viewer;
   viewer.run();
}


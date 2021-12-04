#include "atk/toolkit.h"
#include "atkui/framework.h"
#include "atkui/skeleton_drawer.h"
#include "cyclops.h"
#include "ik_controller.h"
#include <algorithm>
#include <string>

using namespace atk;
using namespace glm;
using namespace std;

class ADancer : public atkui::Framework
{
public:
   ADancer() : atkui::Framework(atkui::Perspective) {}
   virtual ~ADancer() {}

   void setup()
   {
      BVHReader reader;
      reader.load("../motions/Beta/idle.bvh", _skeleton, _motion);
      _drawer.color = vec3(1,0,0);
   }

   void update()
   {
      _motion.update(_skeleton, elapsedTime());

   }

   void scene()
   {  
      update();
      
      IKController ik;
      atk::Joint* lHand = _skeleton.getByName("Beta:LeftHand");
      int jointid = lHand->getID();
      
      float y = 200;
      float j = 2;
      float threshold = 10;
      int maxIters = 50;
      float nudgeFactor = 0.1;
      std::vector<atk::Joint*> chain;
      chain.push_back(lHand);
      atk::Joint* lElbow = lHand->getParent();
      chain.push_back(lElbow);
      atk::Joint* lShoulder = lElbow->getParent();
      chain.push_back(lShoulder);

      if (x == 100) incr = false;
      if (x == 20) incr = true;
      if (incr) x+=j;
      if (!incr) x-=j;
      glm::vec3 goalPos = glm::vec3(x, y, 0);
      ik.solveIKCCD(_skeleton, jointid, goalPos, chain, threshold, maxIters, nudgeFactor);
      
      _drawer.draw(_skeleton, *this);
      setColor(vec3(0,0,1));

      
   }

protected:
   Cyclops _drawer;
   Skeleton _skeleton;
   Motion _motion;

   // Hand target positions
   vec3 _lhandTarget;
   vec3 _rhandTarget;
   bool incr;
   float x = 100;
};

int main(int argc, char** argv)
{
   ADancer viewer;
   viewer.run();
   return 0;
}
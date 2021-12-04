#include "atk/toolkit.h"
#include "atkui/framework.h"
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

      IKController ik;

   }

   void scene()
   {  
      update();
      setColor(vec3(0,0,1));
      

      IKController ik;
      atk::Joint* lHand = _skeleton.getByName("Beta:LeftHand");
      atk::Joint* rHand = _skeleton.getByName("Beta:RightHand");
      int lJointid = lHand->getID();
      int rJointid = rHand->getID();

      int j = 2;
      if (yl == 190) incrl = false;
      if (yl == 90) incrl = true;
      if (incrl) yl+=j;
      if (!incrl) yl-=j;

      if (yr == 190) incrr = false;
      if (yr == 90) incrr = true;
      if (incrr) yr+=j;
      if (!incrr) yr-=j;
      _lhandTarget = vec3(40, yl, 30);
      _rhandTarget = vec3(-40, yr, 30);
 
      ik.solveIKAnalytic(_skeleton, lJointid, _lhandTarget, 0.0001);
      ik.solveIKAnalytic(_skeleton, rJointid, _rhandTarget, 0.0001);
      _drawer.draw(_skeleton, *this);
      // drawSphere(_lhandTarget, 10);
      // drawSphere(_rhandTarget, 10);

   }

protected:
   Cyclops _drawer;
   Skeleton _skeleton;
   Motion _motion;

   // Hand target positions
   bool incrl;
   bool incrr;
   float yl = 100;
   float yr = 140;
   vec3 _lhandTarget = vec3(25, yl, 20);
   vec3 _rhandTarget = vec3(-25, yr, 20);
   
};

int main(int argc, char** argv)
{
   ADancer viewer;
   viewer.run();
   return 0;
}


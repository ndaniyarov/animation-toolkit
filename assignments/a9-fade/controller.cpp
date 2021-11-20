#include "atkui/framework.h"
#include "atkui/skeleton_drawer.h"
#include "atk/toolkit.h"
#include <iostream>
#include <cmath>

using namespace glm;
using namespace std;
using namespace atk;

class WASDSimple : public atkui::Framework
{
public:
  WASDSimple() : atkui::Framework(atkui::Perspective) {}

  virtual void setup()
  {
    BVHReader reader;
    reader.load("../motions/Beta/walking.bvh", _skeleton, _walk);
    _drawer.showAxes = true;
  }

  virtual void scene()
  {
    update();
    
    _drawer.draw(_skeleton, *this);

    // draw heading
    vec3 p = _skeleton.getRoot()->getGlobalTranslation();
    p[1] = 10; // set height close above the floor

    setColor(vec3(0, 1, 1));
    push();
    translate(p);
    rotate(_heading, vec3(0, 1, 0));
    translate(vec3(0,0,25));
    scale(vec3(10, 10, 50));
    drawCylinder(vec3(0), 1.0f);
    pop();
  }

  virtual void update()
  {
    _walk.update(_skeleton, elapsedTime());
    vec3 origPos = _walk.getKey(0).rootPos;
    vec3 pos;
    quat rot = glm::angleAxis(_heading, vec3(0,1,0));
    for (int i = 0; i < _walk.getNumKeys(); i++) {
      Pose p = _walk.getKey(i);
      p.rootPos = origPos;
      p.jointRots[0] = rot;
      _walk.editKey(i, p);
    }

    glm::vec3 moveFwd = _skeleton.getByName("Beta:Head")->getLocal2Global().transformVector(glm::vec3(0,0,-190));
    // TODO: Override the default camera to follow the character
    lookAt(_skeleton.getByName("Beta:Head")->getGlobalTranslation()+moveFwd, _skeleton.getByName("Beta:Head")->getGlobalTranslation(), vec3(0, 1, 0));

    // update heading when key is down
    if (keyIsDown('D')) _heading -= 0.05;
    if (keyIsDown('A')) _heading += 0.05;
  }

protected:
  float _heading;

  Motion _walk;
  Skeleton _skeleton;
  atkui::SkeletonDrawer _drawer;
};

int main(int argc, char **argv)
{
  WASDSimple viewer;
  viewer.run();
}

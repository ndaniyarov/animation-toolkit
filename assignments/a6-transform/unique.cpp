#include "atkui/framework.h"
#include "atk/toolkit.h"
#include "atkmath/quaternion.h"
#include <cmath>
using glm::quat;

using namespace atk;
using glm::vec3;
using agl::Window;

class Tentacle : public atkui::Framework {
public:
   Tentacle() : atkui::Framework(atkui::Perspective) {}
   virtual ~Tentacle() {}

   virtual void setup() {
      lookAt(vec3(300), vec3(0));

      Joint* root  = new Joint("root");
      root->setLocalTranslation(vec3(0,50,0));
      _tentacle.addJoint(root);

    //hind left leg
      Joint* lleg1  = new Joint("lleg1");
      lleg1->setLocalTranslation(vec3(-50,30,-30));
      _tentacle.addJoint(lleg1, root);

      Joint* lleg11  = new Joint("lleg11");
      lleg11->setLocalTranslation(vec3(-20,-40,-20));
      _tentacle.addJoint(lleg11, lleg1);

      Joint* lleg111  = new Joint("lleg111");
      lleg111->setLocalTranslation(vec3(0,-40,-0));
      _tentacle.addJoint(lleg111, lleg11);
    //hind right leg
      Joint* rleg1  = new Joint("rleg1");
      rleg1->setLocalTranslation(vec3(50,30,-30));
      _tentacle.addJoint(rleg1, root);

      Joint* rleg11  = new Joint("rleg11");
      rleg11->setLocalTranslation(vec3(20,-40,-20));
      _tentacle.addJoint(rleg11, rleg1);

      Joint* rleg111  = new Joint("rleg111");
      rleg111->setLocalTranslation(vec3(0,-40,-0));
      _tentacle.addJoint(rleg111, rleg11);

    //middle right leg
      Joint* rleg2  = new Joint("rleg2");
      rleg2->setLocalTranslation(vec3(50,30,0));
      _tentacle.addJoint(rleg2, root);

      Joint* rleg22  = new Joint("rleg22");
      rleg22->setLocalTranslation(vec3(20,-40,0));
      _tentacle.addJoint(rleg22, rleg2);

      Joint* rleg222  = new Joint("rleg222");
      rleg222->setLocalTranslation(vec3(0,-40,-0));
      _tentacle.addJoint(rleg222, rleg22);

    //middle left leg
      Joint* lleg2  = new Joint("lleg2");
      lleg2->setLocalTranslation(vec3(-50,30,0));
      _tentacle.addJoint(lleg2, root);

      Joint* lleg22  = new Joint("lleg22");
      lleg22->setLocalTranslation(vec3(-20,-40,0));
      _tentacle.addJoint(lleg22, lleg2);

      Joint* lleg222  = new Joint("lleg222");
      lleg222->setLocalTranslation(vec3(0,-40,0));
      _tentacle.addJoint(lleg222, lleg22);

    //front right leg 
      Joint* rleg3  = new Joint("rleg3");
      rleg3->setLocalTranslation(vec3(50,30,30));
      _tentacle.addJoint(rleg3, root);

      Joint* rleg33  = new Joint("rleg33");
      rleg33->setLocalTranslation(vec3(20,-40,20));
      _tentacle.addJoint(rleg33, rleg3);

      Joint* rleg333  = new Joint("rleg333");
      rleg333->setLocalTranslation(vec3(0,-40,0));
      _tentacle.addJoint(rleg333, rleg33);
    //front left leg
      Joint* lleg3  = new Joint("lleg3");
      lleg3->setLocalTranslation(vec3(-50,30,30));
      _tentacle.addJoint(lleg3, root);

      Joint* lleg33  = new Joint("lleg33");
      lleg33->setLocalTranslation(vec3(-20,-40,20));
      _tentacle.addJoint(lleg33, lleg3);

      Joint* lleg333  = new Joint("lleg333");
      lleg333->setLocalTranslation(vec3(0,-40,-0));
      _tentacle.addJoint(lleg333, lleg33);

      _tentacle.fk(); // compute local2global transforms
   }

   virtual void scene()
   {
      
      _tentacle.fk(); // computes local2global transforms
      setColor(vec3(.8,.5,.8));
      
      //std::cout<<_tentacle.getNumJoints();
      for (int i = 1; i < _tentacle.getNumJoints(); i++){
        vec3 current = _tentacle.getByID(0)->getLocalTranslation();
        _tentacle.getByID(0)->setLocalTranslation(vec3(0,50,50*elapsedTime()));
        drawSphere(_tentacle.getByID(0)->getGlobalTranslation(), 20);
        Joint* child = _tentacle.getByID(i);
        Joint* parent = child->getParent();
        quat s = glm::angleAxis(0.1f*sin(10*elapsedTime() + i), vec3(1,0,0));
        vec3 globalParentPos = parent->getGlobalTranslation();
        vec3 globalPos = child->getGlobalTranslation();
        child->setLocalRotation(s);
         drawEllipsoid(globalParentPos, globalPos, 10);
      }
   }

protected:
   Skeleton _tentacle;
};

int main(int argc, char** argv)
{
   Tentacle viewer;
   viewer.run();
} 


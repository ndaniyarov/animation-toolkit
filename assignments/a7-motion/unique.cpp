#include <iostream>
#include "atkui/framework.h"
#include "atk/toolkit.h"

using namespace glm;
using namespace atk;

class MotionViewer : public atkui::Framework
{
public:
   MotionViewer() : atkui::Framework(atkui::Perspective) {
   }

   void setup() {
      BVHReader reader;
      reader.load("../motions/Beta/samba_dancing.bvh", skeleton, motion);
      motion.update(skeleton, 0);
   }

   void scene() {
      if (pressed0) {
         time = 0;
         pressed0 = false;
      }
      if (paused) {
         if (pressedPeriod) {
            time = time + motion.getDeltaTime();
            pressedPeriod = false;
         }
         else if (pressedComma){
            time = time - motion.getDeltaTime();
            pressedComma = false;
         }
         motion.update(skeleton, time);
      }
      if (pressedIncreaseSpeed) {
         timeScale += 0.1;
         motion.setDeltaTime(motion.getDeltaTime() - 0.01);
         motion.update(skeleton, time);
         pressedIncreaseSpeed = false;
      }
      if (pressedDecreaseSpeed) {
         timeScale -= 0.1;
         motion.update(skeleton, time);
         motion.setDeltaTime(motion.getDeltaTime() + 0.01);
         pressedDecreaseSpeed = false;
         
      }
      if (!paused)   {
         time += dt();
         motion.update(skeleton, time);
      }

         currentFrame = motion.getFramerate()*time;
      setColor(vec3(0.8,0,0.8));
      for (int i = 0; i < skeleton.getNumJoints(); i++) {
         Joint* joint = skeleton.getByID(i);
         if (joint->getParent() == 0) continue;

         vec3 p1 = joint->getGlobalTranslation();
         vec3 p2 = joint->getParent()->getGlobalTranslation();
         drawSphere(p1, 45);
      }

      drawText(paused? "Paused" : "Playing", 10, 15);
      drawText("Current frame: "+std::to_string(currentFrame), 10, 35);
      drawText("Time scale: "+std::to_string(timeScale), 10, 55);
   }

   virtual void keyUp(int key, int mods) {
      if (key == GLFW_KEY_P) {
         paused = !paused;
      }
      if (key == GLFW_KEY_0) {
         pressed0 = true;
      }
      if (key == GLFW_KEY_PERIOD) {
         pressedPeriod = true;
      }
      if (key == GLFW_KEY_COMMA) {
         pressedComma = true;
      }
      if (key == GLFW_KEY_RIGHT_BRACKET) {
         pressedIncreaseSpeed = true;
      }
      if (key ==GLFW_KEY_LEFT_BRACKET) {
         pressedDecreaseSpeed = true;
      }
   }

private:
   Skeleton skeleton;
   Motion motion;

   float timeScale = 1.0f;
   int currentFrame = 0; 
   bool paused = false;
   bool pressed0 = false;
   bool pressedPeriod = false;
   bool pressedComma = false;
   bool pressedIncreaseSpeed = false;
   bool pressedDecreaseSpeed = false;
   float time = 0;
};


int main(int argc, char** argv) {
   MotionViewer viewer;
   viewer.run();
}

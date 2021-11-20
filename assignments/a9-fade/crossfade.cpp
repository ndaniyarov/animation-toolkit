#include "atk/toolkit.h"
#include "atkui/framework.h"
#include "atkui/skeleton_drawer.h"
#include <stdio.h>
#include <string.h>

using namespace atk;
using namespace atkui;
using namespace glm;

class ACrossfadeViewer : public atkui::Framework
{
public:
  ACrossfadeViewer() : atkui::Framework(atkui::Perspective) {}
  virtual ~ACrossfadeViewer() {}

  void loadMotion1(const std::string &filename)
  {
    BVHReader reader;
    reader.load(filename, skeleton_, motion1_);
  }

  void loadMotion2(const std::string &filename)
  {
    BVHReader reader;
    reader.load(filename, skeleton_, motion2_);
  }

  void crossfade(int numBlendFrames)
  {
    assert(motion1_.getNumKeys() > 0);
    assert(motion2_.getNumKeys() > 0);
    assert(numBlendFrames > 0);
    assert(numBlendFrames <= motion1_.getNumKeys());
    assert(numBlendFrames <= motion2_.getNumKeys());

    blend_.setFramerate(motion1_.getFramerate());
    int start1 = motion1_.getNumKeys() - 1;
    int start2 = 0;

    for (int i = 0; i < motion1_.getNumKeys(); i++) {
      blend_.appendKey(motion1_.getKey(i));
    }

    vec3 dDesired = motion1_.getKey(motion1_.getNumKeys()-1).rootPos;
    quat rDesired = motion1_.getKey(motion1_.getNumKeys()-1).jointRots[0];
    Transform desired = Transform(rDesired, dDesired);

    vec3 dJump = motion2_.getKey(0).rootPos;
    quat rJump = motion2_.getKey(0).jointRots[0];
    Transform jump = Transform(rJump,dJump);

    Transform offset = desired * jump.inverse();

    for (int i = 0; i < motion2_.getNumKeys(); i++) {
      Pose p2 = motion2_.getKey(i);
      vec3 d3 = p2.rootPos;
      quat r3 = p2.jointRots[0];
      Transform current2 = Transform(r3, d3);
      current2 = offset * current2;
      p2.rootPos = current2.t();
      p2.jointRots[0] = current2.r();
      motion2_.editKey(i, p2);
    }

    for (float i = 0; i <=1; i+=0.1){
      Pose p = Pose::Lerp(motion1_.getKey(start1), motion2_.getKey(start2), i);
      blend_.appendKey(p);
    }
    for (int i = 0; i < motion2_.getNumKeys(); i++) {
      blend_.appendKey(motion2_.getKey(i));
    }
  }

  void save(const std::string &filename)
  {
    BVHWriter writer;
    writer.save(filename, skeleton_, blend_);
  }

  void scene()
  {
    blend_.update(skeleton_, elapsedTime());
    drawer_.draw(skeleton_, *this);
  }

private:
  Skeleton skeleton_;
  SkeletonDrawer drawer_;
  Motion motion1_;
  Motion motion2_;
  Motion blend_;
};

std::string PruneName(const std::string &name)
{
  int idx1 = name.find_last_of("/");
  int idx2 = name.find_last_of(".");
  return name.substr(idx1 + 1, idx2 - idx1 - 1);
}

int main(int argc, char **argv)
{
  std::string motion1 = "../motions/Beta/walking.bvh";
  std::string motion2 = "../motions/Beta/jump.bvh";
  int numFrames = 10;

  try
  {
    for (int i = 0; i < argc; i++)
    {
      if (strncmp(argv[i], "-m1", 3) == 0)
        motion1 = argv[i + 1];
      else if (strncmp(argv[i], "-m2", 3) == 0)
        motion2 = argv[i + 1];
      else if (strncmp(argv[i], "-nframes", 7) == 0)
        numFrames = std::stoi(argv[i + 1]);
    }
  }
  catch (const std::exception &e)
  {
    std::cout << "usage: crossfade -m1 <path> -m2 <path> -nframes <num frames>\n";
  }

  ACrossfadeViewer viewer;
  viewer.loadMotion1(motion1);
  viewer.loadMotion2(motion2);
  viewer.crossfade(numFrames);

  std::string saveName = "blend-" + PruneName(motion1) + PruneName(motion2);
  saveName += "-" + std::to_string(numFrames) + ".bvh";
  viewer.save(saveName);

  viewer.run();
  return 0;
}

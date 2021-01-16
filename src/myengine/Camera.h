#include "Component.h"

#include <rend/rend.h>

namespace myengine
{

struct Camera : public Component
{
  void onInitialize();
  void onTick();

  rend::mat4 getView();
  std::shared_ptr<rend::RenderTexture> getRenderTexture();

  std::shared_ptr<rend::RenderTexture> addRenderTexture();

  //
  rend::mat4x4 perspectiveMatrix;
  float fovy, aspect, near, far, pitch, yaw;
  rend::vec3 direction;
  //

private:
  std::shared_ptr<rend::RenderTexture> renderTexture;

};

}


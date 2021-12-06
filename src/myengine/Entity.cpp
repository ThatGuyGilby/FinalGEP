#include "Entity.h"
#include "Component.h"
#include "Transform.h"

namespace myengine
{

void Entity::tick()
{
  for(size_t ci = 0; ci < components.size(); ci++)
  {
    components.at(ci)->tick();
  }
}

void Entity::render()
{
  for(size_t ci = 0; ci < components.size(); ci++)
  {
    components.at(ci)->render();
  }
}

void Entity::collisionEnter(std::shared_ptr<Rigidbody> other)
{
    for (size_t ci = 0; ci < components.size(); ci++)
    {
        components.at(ci)->collisionEnter(other);
    }
}

void Entity::collisionStay(std::shared_ptr<Rigidbody> other)
{
    for (size_t ci = 0; ci < components.size(); ci++)
    {
        components.at(ci)->collisionStay(other);
    }
}

void Entity::collisionLeave(std::shared_ptr<Rigidbody> other)
{
    for (size_t ci = 0; ci < components.size(); ci++)
    {
        components.at(ci)->collisionLeave(other);
    }
}

std::shared_ptr<Core> Entity::getCore()
{
  return core.lock();
}

std::shared_ptr<Transform> Entity::getTransform()
{
  return getComponent<Transform>();
}

}


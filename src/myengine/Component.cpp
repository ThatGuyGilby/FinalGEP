#include "Component.h"
#include "Entity.h"
#include "Rigidbody.h"
#include <iostream>

namespace myengine
{

void Component::tick()
{
  onTick();
}

void Component::render()
{
  onRender();
}

void Component::collisionEnter(std::shared_ptr<Rigidbody> other)
{
	onCollisionEnter(other);
}

void Component::collisionStay(std::shared_ptr<Rigidbody> other)
{
	onCollisionStay(other);
}

void Component::collisionLeave(std::shared_ptr<Rigidbody> other)
{
	onCollisionLeave(other);
}

void Component::onInitialize() { }
void Component::onTick() { }
void Component::onRender() { }

void Component::onCollisionEnter(std::shared_ptr<Rigidbody> other) { }
void Component::onCollisionStay(std::shared_ptr<Rigidbody> other) { }
void Component::onCollisionLeave(std::shared_ptr<Rigidbody> other) { }

std::shared_ptr<Entity> Component::getEntity()
{
  return entity.lock();
}

std::shared_ptr<Core> Component::getCore()
{
  return getEntity()->getCore();
}

std::shared_ptr<Transform> Component::getTransform()
{
  return getEntity()->getTransform();
}

}

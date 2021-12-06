#ifndef MYENGINE_RIGIDBODY_H
#define MYENGINE_RIGIDBODY_H

#include "Component.h"
#include <rend/rend.h>

namespace myengine
{
	
struct BoxCollider;

struct Rigidbody : public Component
{
	void onInitialize();
	void onTick();

	void MovePosition(rend::vec3 position);

	std::shared_ptr<BoxCollider> collider;

	int id;

	rend::vec3 velocity;

	bool CheckCollision(rend::vec3 position);

	std::vector<std::shared_ptr<Rigidbody>> collisionCache;

	bool gravity;
};

struct BoxCollider : Component
{
	rend::vec3 size;
	rend::vec3 center;

	void onInitialize(rend::vec3 size)
	{
		size = rend::vec3(size);
		center = rend::vec3(0);
	}

	void onInitialize()
	{
		size = rend::vec3(1);
		center = rend::vec3(0);
	}
};

}

#endif
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
};

struct BoxCollider
{
	rend::vec3 size;
	rend::vec3 center;

	BoxCollider()
	{
		size = rend::vec3(1);
		center = rend::vec3(0);
	}
};

}

#endif
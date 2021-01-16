#include "Rigidbody.h"
#include "Core.h"
#include "Entity.h"
#include "Transform.h"
#include <iostream>

namespace myengine
{
	void Rigidbody::onInitialize()
	{
		std::shared_ptr<Rigidbody> self = getEntity()->getComponent<Rigidbody>();
		getCore()->rigidbodies.push_back(self);

		std::shared_ptr<BoxCollider> tCollider = std::make_shared<BoxCollider>();
		//tCollider->center = getEntity()->getTransform()->position;
		std::cout << "Size: " << tCollider->size.x << ", " << tCollider->size.y << ", " << tCollider->size.z << std::endl;
		std::cout << "Center: " << tCollider->center.x << ", " << tCollider->center.y << ", " << tCollider->center.z << std::endl;

		id = getCore()->GetID();

		collider = tCollider;
	}

	void Rigidbody::onTick()
	{

	}

	void Rigidbody::MovePosition(rend::vec3 position)
	{
		bool collision = false;

		rend::vec3 m_position = getEntity()->getTransform()->position + position + collider->center;

		rend::vec2 m_xrange = rend::vec2(m_position.x - (collider->size.x / 2), m_position.x + (collider->size.x / 2));
		rend::vec2 m_yrange = rend::vec2(m_position.y - (collider->size.y / 2), m_position.y + (collider->size.y / 2));
		rend::vec2 m_zrange = rend::vec2(m_position.z - (collider->size.z / 2), m_position.z + (collider->size.z / 2));

		for (int i = 0; i < getCore()->rigidbodies.size(); i++)
		{
			std::shared_ptr<Rigidbody> rb = getCore()->rigidbodies[i];

			if (rb->id != id)
			{
				rend::vec3 o_position = rb->getTransform()->position + rb->collider->center;

				rend::vec2 o_xrange = rend::vec2(o_position.x - (rb->collider->size.x / 2), o_position.x + (rb->collider->size.x / 2));
				rend::vec2 o_yrange = rend::vec2(o_position.y - (rb->collider->size.y / 2), o_position.y + (rb->collider->size.y / 2));
				rend::vec2 o_zrange = rend::vec2(o_position.z - (rb->collider->size.z / 2), o_position.z + (rb->collider->size.z / 2));

				if (m_xrange.y > o_xrange.x &&
					m_xrange.x < o_xrange.y &&
					m_yrange.y > o_yrange.x &&
					m_yrange.x < o_yrange.y &&
					m_zrange.y > o_zrange.x &&
					m_zrange.x < o_zrange.y)
				{
					collision = true;
				}
			}
		}

		if (!collision)
		{
			getEntity()->getTransform()->position += position;
		}
	}
}
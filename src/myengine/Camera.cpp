#include "Camera.h"
#include "Core.h"
#include "Entity.h"
#include "Transform.h"

namespace myengine
{

void Camera::onInitialize()
{
	std::shared_ptr<Camera> self = getEntity()->getComponent<Camera>();
	getCore()->cameras.push_back(self);

	fovy = 45;
	aspect = 1;
	near = 0.1;
	far = 100;
	perspectiveMatrix = rend::perspective(rend::radians(fovy), aspect, near, far);

	pitch = 0;
	yaw = 0;
	getTransform()->rotation.x = -90;
}

void Camera::onTick()
{
	if (pitch > 89.0f) pitch = 89.0f;
	if (pitch < -89.0f) pitch = -89.0f;

	yaw = getTransform()->rotation.x;

	direction = rend::normalize(rend::vec3(
		cos(rend::radians(yaw)) * cos(rend::radians(pitch)),
		sin(rend::radians(pitch)),
		sin(rend::radians(yaw)) * cos(rend::radians(pitch))
	));

}

rend::mat4 Camera::getView()
{
	//return rend::inverse(getTransform()->getModel());

	rend::vec3 position = getTransform()->position;

	return rend::lookAt(position, position + rend::normalize(direction), rend::vec3(0, 1, 0));
	//return rend::inverse(getTransform()->getModel());
}

std::shared_ptr<rend::RenderTexture> Camera::getRenderTexture()
{
	return renderTexture;
}

std::shared_ptr<rend::RenderTexture> Camera::addRenderTexture()
{
	renderTexture = getCore()->context->createRenderTexture();

	return renderTexture;
}

}


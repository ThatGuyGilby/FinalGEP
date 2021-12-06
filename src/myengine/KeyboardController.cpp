#include "KeyboardController.h"
#include "Core.h"
#include "Entity.h"
#include <iostream>

namespace myengine
{
	void KeyboardController::onTick()
	{
		rend::vec2 velocity(0.0f, 0.0f);

		const Uint8* keyState = SDL_GetKeyboardState(NULL);

		if (keyState[SDL_SCANCODE_A]) velocity.x -= 0.02;
		if (keyState[SDL_SCANCODE_D]) velocity.x += 0.02;
		if (keyState[SDL_SCANCODE_W]) velocity.y += 0.02;
		if (keyState[SDL_SCANCODE_S]) velocity.y -= 0.02;

		if (velocity.x != 0 && velocity.y != 0) velocity *= 0.5f;

		getEntity()->transform->position += velocity;
	};
}
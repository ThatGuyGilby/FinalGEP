#include <SDL2/SDL.h>
#include <rend/rend.h>
#include <AL/al.h>
#include <AL/alc.h>
#include <memory>
#include <vector>
#include <iostream>

namespace myengine
{

struct Renderer;
struct Entity;
struct Keyboard;
struct Camera;
struct Resources;
struct Rigidbody;
struct Model;

struct Core
{
	static std::shared_ptr<Core> initialize();

	std::shared_ptr<Entity> addEntity();
	std::shared_ptr<Keyboard> getKeyboard();
	std::shared_ptr<Camera> getCamera();
	std::shared_ptr<Resources> getResources();

	void start();

	std::vector<std::shared_ptr<Rigidbody>> rigidbodies;

	int current_id = -2147483648;
	int GetID()
	{
		current_id++;
		std::cout << "Generated New ID: " << current_id - 1 << std::endl;
		return current_id - 1;
	}

	ALCdevice* audioDevice;
	ALCcontext* audioContext;


private:
	friend struct myengine::Camera;
	friend struct myengine::Rigidbody;
	friend struct myengine::Renderer;
	friend struct myengine::Model;

	std::vector<std::shared_ptr<Entity> > entities;
	std::weak_ptr<Core> self;
	SDL_Window* window;
	SDL_GLContext glContext;
	std::shared_ptr<rend::Context> context;
	std::shared_ptr<Keyboard> keyboard;
	std::shared_ptr<Resources> resources;

	std::weak_ptr<Camera> currentCamera;
	std::vector<std::weak_ptr<Camera>> cameras;

};

}

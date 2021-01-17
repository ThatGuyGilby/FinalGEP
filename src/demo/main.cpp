#include <myengine/myengine.h>

struct Controller : public Component
{
    void MovePosition(rend::vec3 velocity)
    {
        getEntity()->getComponent<Rigidbody>()->MovePosition(velocity);
        //getTransform()->setPosition(getTransform()->position + velocity);
        //getTransform()->translate(velocity.x, velocity.y, velocity.z);
    }

    void Movement()
    {
        float speed = 0.25;
        rend::vec3 velocity = rend::vec3(0, 0, 0);
        rend::vec3 tunedDirection = getCore()->getCamera()->direction;

        if (getCore()->getKeyboard()->getKey('w'))
        {
            velocity += speed * tunedDirection;
        }

        if (getCore()->getKeyboard()->getKey('s'))
        {
            velocity -= speed * tunedDirection;
        }

        if (getCore()->getKeyboard()->getKey('a'))
        {
            velocity -= rend::cross(tunedDirection, rend::vec3(0, 1, 0)) * speed;
        }

        if (getCore()->getKeyboard()->getKey('d'))
        {
            velocity += rend::cross(tunedDirection, rend::vec3(0, 1, 0)) * speed;
        }

        velocity.y = 0;
        //std::cout << "x: " << velocity.x << " y: " << velocity.y << " z:" << velocity.z << std::endl;
        MovePosition(velocity);
    }

    void onTick()
    {
        if (getCore()->getCamera() == nullptr) return;

        Movement();

        if (getCore()->getKeyboard()->getKey('e'))
        {
            getTransform()->rotate(1, 0, 0);
        }

        if (getCore()->getKeyboard()->getKey('q'))
        {
            getTransform()->rotate(-1, 0, 0);
        }

        //std::cout << "x: " << getTransform()->rotation.x << " y: " << getTransform()->rotation.y << " z: " << getTransform()->rotation.z << std::endl;
    }
};

int main()
{
  std::shared_ptr<Core> core = Core::initialize();

  // Add our man curuthers
  std::shared_ptr<Entity> curuthers = core->addEntity();
  curuthers->getTransform()->setPosition(rend::vec3(-2, 1000, -10));
  curuthers->addComponent<Renderer>("curuthers/curuthers");
  curuthers->addComponent<Rigidbody>();
  
  // Add our man curuthers
  std::shared_ptr<Entity> curuthers2 = core->addEntity();
  curuthers2->getTransform()->setPosition(rend::vec3(0, 10, -10));
  curuthers2->addComponent<Renderer>("curuthers/curuthers");
  curuthers2->addComponent<Rigidbody>();
  
  // Add our man curuthers
  std::shared_ptr<Entity> curuthers3 = core->addEntity();
  curuthers3->getTransform()->setPosition(rend::vec3(2, 100, -10));
  curuthers3->addComponent<Renderer>("curuthers/curuthers");
  curuthers3->addComponent<Rigidbody>();

  std::shared_ptr<Entity> player = core->addEntity();
  player->addComponent<Camera>();
  player->addComponent<Controller>();
  player->addComponent<Rigidbody>();
  player->getTransform()->setPosition(rend::vec3(0, 0, 0));

  core->start();

  return 0;
}

#include <myengine/myengine.h>

struct CuruthersBase : public Component
{
  void onInitialize(int team, int type, std::string name)
  {
    std::shared_ptr<Renderer> r = getEntity()->addComponent<Renderer>();

    std::shared_ptr<Model> cm = getCore()->getResources()->
      load<Model>("../models/curuthers/curuthers");

    r->setModel(cm);
  }

  //void onGui()ed
  //{
  //  getCore()->getGui()->draw(rt, 0, 0, 100, 100);
  //}
};

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
  curuthers->getTransform()->setPosition(rend::vec3(0, 0, -10));
  curuthers->addComponent<CuruthersBase>(1, 2, "Karsten");
  curuthers->addComponent<Rigidbody>();

  std::shared_ptr<Entity> curuthers2 = core->addEntity();
  curuthers2->getTransform()->setPosition(rend::vec3(-10, 0, 10));
  curuthers2->addComponent<CuruthersBase>(1, 2, "Karsten");
  curuthers2->addComponent<Rigidbody>();
  /*
   * Add sample object to collide against
   */
  //std::shared_ptr<Entity> pe2 = core->addEntity();
  //std::shared_ptr<Renderer> r2 = pe2->addComponent<Renderer>();
  //r2->getTransform()->setPosition(rend::vec3(2, 1, -5));

  std::shared_ptr<Entity> player = core->addEntity();
  player->addComponent<Camera>();
  player->addComponent<Controller>();
  player->addComponent<Rigidbody>();

  core->start();

  return 0;
}

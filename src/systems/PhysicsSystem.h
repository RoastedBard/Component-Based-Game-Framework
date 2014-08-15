#ifndef _PHYSICSSYSTEM_H_
#define _PHYSICSSYSTEM_H_

#include "isystem.h"
#include "PlatformerController.h"
#include "MovementComponent.h"
#include "PlatformerPhysicsComponent.h"
#include <memory>
#include <vector>

using namespace std;

class PhysicsSystem :
    public ISystem
{
public:
    PhysicsSystem(void);
    ~PhysicsSystem(void);

    static shared_ptr<PhysicsSystem> instance();

public:
    virtual void addComponent(GameObject *ownerGameObject, unsigned componentType);
    virtual shared_ptr<IComponent> getComponent(const ComponentHandle& handle);

    virtual unsigned getSizeOfComponentArray(unsigned type) const;
    void update(float deltaTime);

private:
    vector<shared_ptr<MovementComponent>>              _movementComponents;
    vector<shared_ptr<PlatformerPhysicsComponent>>     _physicsComponents;

    static shared_ptr<PhysicsSystem> _instance;
};

#endif
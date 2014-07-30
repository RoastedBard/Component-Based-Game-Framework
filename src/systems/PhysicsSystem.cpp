#include <iostream>
#include "PhysicsSystem.h"
#include "Enums.h"

shared_ptr<PhysicsSystem> PhysicsSystem::_instance = nullptr;

PhysicsSystem::PhysicsSystem(void)
{
}

PhysicsSystem::~PhysicsSystem(void)
{
    cout<<"~Destroying PhysicsSystem\n";
}

shared_ptr<PhysicsSystem> PhysicsSystem::instance()
{
    if(_instance == nullptr)
    {
        _instance.reset(new PhysicsSystem());
        return _instance;
    }

    return _instance;
}

void PhysicsSystem::update(float deltaTime)
{
    for(size_t i = 0; i < _physicsComponents.size(); ++i)
        _physicsComponents[i]->update(deltaTime);
}

unsigned PhysicsSystem::getSizeOfComponentArray(unsigned type) const
{
    switch(type)
    {
    case COMPONENT_MOVEMENT:
        return _movementComponents.size();

    case COMPONENT_PLATFORMER_PHYSICS:
        return _physicsComponents.size();
    }
}

void PhysicsSystem::addComponent(GameObject *ownerGameObject, unsigned componentType)
{
    switch(componentType)
    {
    case COMPONENT_MOVEMENT:
        _movementComponents.push_back(make_shared<MovementComponent>());
        _movementComponents.back()->setOwner(ownerGameObject);
        break;

    case COMPONENT_PLATFORMER_PHYSICS:
        _physicsComponents.push_back(make_shared<PlatformerPhysicsComponent>());
        _physicsComponents.back()->setOwner(ownerGameObject);
        break;
    }
}

shared_ptr<IComponent> PhysicsSystem::getComponent(const ComponentHandle& handle)
{
    switch(handle.type)
    {
    case COMPONENT_MOVEMENT:
        return _movementComponents[handle.arrayIndex];

    case COMPONENT_PLATFORMER_PHYSICS:
        return _physicsComponents[handle.arrayIndex];

    default:
        return nullptr;
    }
}
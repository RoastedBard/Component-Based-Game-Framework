#include "Enums.h"
#include "ComponentFabric.h"
#include "RenderingSystem.h"
#include "PhysicsSystem.h"
#include "InputSystem.h"

shared_ptr<ComponentFabric> ComponentFabric::_instance = nullptr;

ComponentFabric::ComponentFabric(void)
{
}


ComponentFabric::~ComponentFabric(void)
{
}

shared_ptr<ComponentFabric> ComponentFabric::instance()
{
    if(_instance == nullptr)
    {
        _instance.reset(new ComponentFabric);
        return _instance;
    }

    return _instance;
}

ComponentHandle ComponentFabric::addComponent(GameObject *ownerGameObject, unsigned type)
{
    ComponentHandle newCompHandle;

    newCompHandle.type = type;

    switch(type)
    {
    case COMPONENT_ANIMATION:

        RenderingSystem::instance()->addComponent(ownerGameObject, type); // Adding a component
        
        newCompHandle.arrayIndex =  RenderingSystem::instance()->getSizeOfComponentArray(COMPONENT_ANIMATION) - 1; // Taking index in array of Components
        
        return newCompHandle;

    case COMPONENT_PLATFORMER_CONTROLLER:

        InputSystem::instance()->addComponent(ownerGameObject, type);

        newCompHandle.arrayIndex = InputSystem::instance()->getSizeOfComponentArray() - 1;

        return newCompHandle;

    case COMPONENT_MOVEMENT:

        PhysicsSystem::instance()->addComponent(ownerGameObject, type);

        newCompHandle.arrayIndex = PhysicsSystem::instance()->getSizeOfComponentArray(COMPONENT_MOVEMENT) - 1;

        return newCompHandle;

    case COMPONENT_PLATFORMER_PHYSICS:
        
        PhysicsSystem::instance()->addComponent(ownerGameObject, type);
        
        newCompHandle.arrayIndex = PhysicsSystem::instance()->getSizeOfComponentArray(COMPONENT_PLATFORMER_PHYSICS) - 1;

        return newCompHandle;

    case COMPONENT_SPRITE:
        
        RenderingSystem::instance()->addComponent(ownerGameObject, type);
        
        newCompHandle.arrayIndex = RenderingSystem::instance()->getSizeOfComponentArray(COMPONENT_SPRITE) - 1;

        return newCompHandle;
    }
}

shared_ptr<IComponent> ComponentFabric::getComponent(ComponentHandle handle)
{
    switch(handle.type)
    {
    case COMPONENT_ANIMATION:
        return RenderingSystem::instance()->getComponent(handle);

    case COMPONENT_PLATFORMER_CONTROLLER:
        return InputSystem::instance()->getComponent(handle);

    case COMPONENT_MOVEMENT:
        return PhysicsSystem::instance()->getComponent(handle);

    case COMPONENT_PLATFORMER_PHYSICS:
        return PhysicsSystem::instance()->getComponent(handle);

    case COMPONENT_SPRITE:
        return RenderingSystem::instance()->getComponent(handle);
    }

    return nullptr;
}
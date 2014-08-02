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

ComponentHandle ComponentFabric::_addComponent(unsigned type, GameObject *ownerGameObject, shared_ptr<ISystem> system)
{
    ComponentHandle newCompHandle;

    newCompHandle.type = type;

    system->addComponent(ownerGameObject, type); // Adding a component
    
    newCompHandle.arrayIndex =  RenderingSystem::instance()->getSizeOfComponentArray(type) - 1; // Taking index in array of Components
    
    return newCompHandle;
}


ComponentHandle ComponentFabric::addComponent(GameObject *ownerGameObject, unsigned type)
{
    switch(type)
    {
    case COMPONENT_ANIMATION:
        return _addComponent(type, ownerGameObject, RenderingSystem::instance());

    case COMPONENT_PLATFORMER_CONTROLLER:
        return _addComponent(type, ownerGameObject, InputSystem::instance());

    case COMPONENT_MOVEMENT:
        return _addComponent(type, ownerGameObject, PhysicsSystem::instance());

    case COMPONENT_PLATFORMER_PHYSICS:
        return _addComponent(type, ownerGameObject, PhysicsSystem::instance());

    case COMPONENT_SPRITE:
        return _addComponent(type, ownerGameObject, RenderingSystem::instance());
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
#include "GameObject.h"
#include "Enums.h"
#include "TransformComponent.h"
#include "MovementComponent.h"
#include "PlatformerPhysicsComponent.h"
#include "PlatformerController.h"
#include "ComponentFabric.h"
#include <iostream>

GameObject::GameObject()
{
    _transformComponent._position.x = 0;
    _transformComponent._position.y = 0;
}

GameObject::~GameObject()
{
    cout<<"~Destroying GameObject with adress: "<<this<<endl;
}

shared_ptr<IComponent> GameObject::getComponent(unsigned id)
{
    for(size_t i = 0; i < _componentArray.size(); ++i)
    {
        if(id == _componentArray[i].type)
            return ComponentFabric::instance()->getComponent(_componentArray[i]);
    }

    return nullptr;
}

TransformComponent& GameObject::getTranformComponent()
{
    return _transformComponent;
}

void GameObject::addComponent(unsigned type)
{
    ComponentHandle newCompHandle;

    newCompHandle = ComponentFabric::instance()->addComponent(this, type);

    _componentArray.push_back(newCompHandle);
}

bool GameObject::hasComponent(unsigned type) const
{
    for(size_t i = 0; i < _componentArray.size(); ++i)
    {
        if(type == _componentArray[i].type)
            return true;
    }

    return false;
}

void GameObject::updateComponents(float deltaTime)
{
   /* for(size_t i = 0; i < _componentArray.size(); ++i)
    {
        if(ComponentFabric::instance()->getComponent(_componentArray[i])->isUpdateable())
            ComponentFabric::instance()->getComponent(_componentArray[i])->update(deltaTime);
    }*/
}

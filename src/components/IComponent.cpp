#include "IComponent.h"
#include "GameObject.h"
#include <iostream>

IComponent::IComponent(void)
{
    _id = -1;
}

IComponent::~IComponent(void)
{
    cout<<"~Destroying IComponent\n";
    _owner.release();
}

unsigned IComponent::getId() const
{
    return _id;
}

void IComponent::setOwner(GameObject *owner)
{
    _owner.reset(owner);
}

GameObject* IComponent::getOwner()
{
    return _owner.get();
}

bool IComponent::isUpdateable() const
{
    return _isUpdateable;
}
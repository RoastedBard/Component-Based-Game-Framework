#include "TransformComponent.h"
#include "Enums.h"
#include <iostream>

TransformComponent::TransformComponent(void)
{
    _id = COMPONENT_TRANSFORM;
    _isUpdateable = false;

    _position.x = 0;
    _position.y = 0;
}

TransformComponent::~TransformComponent(void)
{
    cout<<"~Destroying TransformComponent\n";
}

void TransformComponent::update(float deltaTime)
{
    cout<<"TransformComponent updating\n";
}
#include "MovementComponent.h"
#include "Enums.h"
#include <iostream>

MovementComponent::MovementComponent(void)
{
    _id = Enums::COMPONENT_MOVEMENT;
    _isUpdateable = false;

    _velocity.x = 0;
    _velocity.y = 0;

    _acceleration.x = 0;
    _acceleration.y = 0;

    _maxVelocity.x = 0;
    _maxVelocity.y = 0;

    _direction = Enums::DIRECTION_NONE;

    _isJumping = false;
    _isOnTheGround = false;
}


MovementComponent::~MovementComponent(void)
{
    cout<<"~Destroying MovementComponent\n";
}

void MovementComponent::update(float deltaTime)
{
}
#include "MovementComponent.h"
#include "Enums.h"
#include <iostream>

MovementComponent::MovementComponent(void)
{
    _id = COMPONENT_MOVEMENT;
    _isUpdateable = false;

    _velocity.x = 0;
    _velocity.y = 0;

    _acceleration.x = 0.03;
    _acceleration.y = 4.75;

    _maxVelocity.x = 0;
    _maxVelocity.y = 0;

    _isJumping = false;
    _isOnTheGround = false;

    _isMovingHorizontal = false;
}


MovementComponent::~MovementComponent(void)
{
    cout<<"~Destroying MovementComponent\n";
}

void MovementComponent::update(float deltaTime)
{
}
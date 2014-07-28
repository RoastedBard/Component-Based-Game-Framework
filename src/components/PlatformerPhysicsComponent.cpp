#include "PlatformerPhysicsComponent.h"
#include "Enums.h"
#include "TransformComponent.h"

#include "GameObject.h"
#include <iostream>

PlatformerPhysicsComponent::PlatformerPhysicsComponent(void)
{
    _id = COMPONENT_PLATFORMER_PHYSICS;
    _isUpdateable = true;
    _gravity.x = 0;
    _gravity.y = 0.3;
}

PlatformerPhysicsComponent::~PlatformerPhysicsComponent(void)
{
    cout<<"~Destroying PlatformerPhysicsComponent\n";
}

void PlatformerPhysicsComponent::update(float deltaTime)
{
    if(movComp == nullptr)
        movComp = static_pointer_cast<MovementComponent>(_owner->getComponent(COMPONENT_MOVEMENT));

    if(movComp->_isJumping)
        _performJumping(deltaTime);
    
    _performMovement(deltaTime);

    _performGravity(deltaTime);
}

float PlatformerPhysicsComponent::_lerp(float max, float current, float acceleration)
{
    float difference;

    difference = max - current;

    if(difference > acceleration)
        return current + acceleration;

    if(difference < (-acceleration))
        return current - acceleration;

    return max;
}

void PlatformerPhysicsComponent::_performGravity(float deltaTime)
{
    if(_owner->getTranformComponent()._position.y >= 400)
    { 
        _owner->getTranformComponent()._position.y = 400;

        movComp->_velocity.y = 0.0;
        movComp->_maxVelocity.y = 0.0f;

        movComp->_isOnTheGround = true;
        movComp->_isJumping = false;
    }
    else
        movComp->_velocity.y += _gravity.y * deltaTime;
}

void PlatformerPhysicsComponent::_performMovement(float deltaTime)
{
    movComp->_velocity.x = _lerp(movComp->_maxVelocity.x, movComp->_velocity.x, movComp->_acceleration.x);
    movComp->_velocity.y = _lerp(movComp->_maxVelocity.y, movComp->_velocity.y, movComp->_acceleration.y);

    _owner->getTranformComponent()._position += movComp->_velocity * deltaTime;
}

void PlatformerPhysicsComponent::_performJumping(float deltaTime)
{
    if(movComp->_isOnTheGround)
    {
        movComp->_isOnTheGround = false;
    }
}
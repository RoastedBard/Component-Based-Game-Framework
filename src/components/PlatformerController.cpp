#include "PlatformerController.h"
#include "TransformComponent.h"
#include "MovementComponent.h"
#include "AnimationComponent.h"
#include "GameObject.h"
#include "Enums.h"
#include "InputHandler.h"
#include <iostream>
#include <memory>

PlatformerController::PlatformerController(void)
{
    _id = COMPONENT_PLATFORMER_CONTROLLER;
    _isUpdateable = true;
}


PlatformerController::~PlatformerController(void)
{
    std::cout<<"~Destroying PlatformerController\n";
}

void PlatformerController::update(float deltaTime)
{
    shared_ptr<MovementComponent> movComp;
    shared_ptr<AnimationComponent> animComp;

    if(_owner->hasComponent(COMPONENT_MOVEMENT))
        movComp = static_pointer_cast<MovementComponent>(_owner->getComponent(COMPONENT_MOVEMENT));
    
    if(_owner->hasComponent(COMPONENT_ANIMATION))
        animComp = static_pointer_cast<AnimationComponent>(_owner->getComponent(COMPONENT_ANIMATION));

    if(movComp->_isOnTheGround == true)
    {
        if(animComp->getCurrentAnimationEnum() == ANIMATION_JUMP_LEFT)
        {
            if(movComp->_isMovingHorizontal == false)
                animComp->setCurrentAnimation(ANIMATION_STAND_LEFT);

            else if(movComp->_isMovingHorizontal == true)
                animComp->setCurrentAnimation(ANIMATION_WALK_LEFT);
        }

        else if(animComp->getCurrentAnimationEnum() == ANIMATION_JUMP_RIGHT)
        {
            if(movComp->_isMovingHorizontal == false)
                animComp->setCurrentAnimation(ANIMATION_STAND_RIGHT);

            else if(movComp->_isMovingHorizontal == true)
                animComp->setCurrentAnimation(ANIMATION_WALK_RIGHT);
        }
    }

    if(TheInputHandler::Instance()->getKeyPressed() == KEY_PRESSED_LEFT)
    {
        movComp->_maxVelocity.x = -0.3f;

        movComp->_isMovingHorizontal = true;

        if(animComp != nullptr)
            animComp->setCurrentAnimation(ANIMATION_WALK_LEFT);
    }

    else if(TheInputHandler::Instance()->getKeyPressed() == KEY_PRESSED_RIGHT)
    {
        movComp->_maxVelocity.x = 0.3f;

        movComp->_isMovingHorizontal = true;

        if(animComp != nullptr)
            animComp->setCurrentAnimation(ANIMATION_WALK_RIGHT);
    }

    else if(TheInputHandler::Instance()->getKeyPressed() == KEY_RELEASED_LEFT)
    {
        movComp->_maxVelocity.x = 0.0f;

        movComp->_isMovingHorizontal = false;

        if(animComp != nullptr)
            animComp->setCurrentAnimation(ANIMATION_STAND_LEFT);
    }

    else if(TheInputHandler::Instance()->getKeyPressed() == KEY_RELEASED_RIGHT)
    {
        movComp->_maxVelocity.x = 0.0f;

        movComp->_isMovingHorizontal = false;

        if(animComp != nullptr)
            animComp->setCurrentAnimation(ANIMATION_STAND_RIGHT);    
    }

    else if(TheInputHandler::Instance()->getKeyPressed() == KEY_PRESSED_SPACE || TheInputHandler::Instance()->getKeyPressed() == KEY_PRESSED_UP)
    {
        movComp->_isJumping = true;

        movComp->_isMovingHorizontal = false;

        movComp->_maxVelocity.y = -0.9f;

        if(animComp != nullptr)
        {
            if(animComp->getCurrentAnimationEnum() == ANIMATION_WALK_LEFT || animComp->getCurrentAnimationEnum() == ANIMATION_STAND_LEFT)
                animComp->setCurrentAnimation(ANIMATION_JUMP_LEFT);

            else if(animComp->getCurrentAnimationEnum() == ANIMATION_WALK_RIGHT || animComp->getCurrentAnimationEnum() == ANIMATION_STAND_RIGHT)
                animComp->setCurrentAnimation(ANIMATION_JUMP_RIGHT);
        }
    }
    

    else if(TheInputHandler::Instance()->getKeyPressed() == KEY_RELEASED_SPACE || TheInputHandler::Instance()->getKeyPressed() == KEY_RELEASED_UP)
    {

    }

    
}
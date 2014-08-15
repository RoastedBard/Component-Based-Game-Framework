#include "PlatformerController.h"
#include "TransformComponent.h"
#include "MovementComponent.h"
#include "GameObject.h"
#include "Enums.h"
#include "InputSystem.h"
#include <iostream>
#include <memory>

PlatformerController::PlatformerController(void)
{
    _id = Enums::COMPONENT_PLATFORMER_CONTROLLER;
    _isUpdateable = true;
}


PlatformerController::~PlatformerController(void)
{
    std::cout<<"~Destroying PlatformerController\n";
}

void PlatformerController::update(float deltaTime)
{
    shared_ptr<MovementComponent> movComp;

    if(_owner->hasComponent(Enums::COMPONENT_MOVEMENT))
        movComp = static_pointer_cast<MovementComponent>(_owner->getComponent(Enums::COMPONENT_MOVEMENT));

    switch(InputSystem::instance()->getKeyPressed())
    {
    case Enums::KEY_PRESSED_LEFT:
        movComp->_maxVelocity.x = -0.3f;
        movComp->_direction = Enums::DIRECTION_LEFT;

        break;

    case Enums::KEY_PRESSED_RIGHT:
        movComp->_maxVelocity.x = 0.3f;
        movComp->_direction = Enums::DIRECTION_RIGHT;

        break;

    case Enums::KEY_RELEASED_LEFT:
        movComp->_maxVelocity.x = 0.0f;
        movComp->_direction = Enums::DIRECTION_NONE;

        break;

    case Enums::KEY_RELEASED_RIGHT:
        movComp->_maxVelocity.x = 0.0f;
        movComp->_direction = Enums::DIRECTION_NONE;

        break;

    case Enums::KEY_PRESSED_SPACE:
    case Enums::KEY_PRESSED_UP:
        movComp->_isJumping = true;
        movComp->_maxVelocity.y = -0.9f;
        movComp->_direction = Enums::DIRECTION_UP;

        break;

    case Enums::KEY_RELEASED_SPACE:
    case Enums::KEY_RELEASED_UP:

        // To prevent further moving in the following case:
        //
        // Enums::KEY_PRESSED_RIGHT
        // 
        // >keyList: Enums::KEY_NONE, Enums::KEY_PRESSED_RIGHT;
        // 
        // Enums::KEY_PRESSED_UP
        //
        // >keyList: Enums::KEY_NONE, Enums::KEY_PRESSED_RIGHT, Enums::KEY_PRESSED_UP;
        // 
        // Enums::KEY_RELEASED_RIGHT
        // --deletion of Enums::KEY_PRESSED_RIGHT
        // >keyList: Enums::KEY_NONE, Enums::KEY_PRESSED_UP;
        //
        // Enums::KEY_RELEASED_UP
        // --deletion of Enums::KEY_PRESSED_UP and insertion of Enums::KEY_RELEASED_UP
        // >keyList: Enums::KEY_NONE, Enums::KEY_RELEASED_UP;
        //
        // Since no Enums::KEY_RELEASED_RIGHT was on the stack, hero will begin to move, cause 'movComp->_maxVelocity.x = 0.0f' was not called, so we call it here:
        
        movComp->_maxVelocity.x = 0.0f; 
        movComp->_direction = Enums::DIRECTION_NONE;

        break;
    }
}
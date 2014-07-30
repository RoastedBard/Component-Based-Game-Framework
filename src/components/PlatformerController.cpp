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

    if(_owner->hasComponent(COMPONENT_MOVEMENT))
        movComp = static_pointer_cast<MovementComponent>(_owner->getComponent(COMPONENT_MOVEMENT));

    switch(InputSystem::instance()->getKeyPressed())
    {
    case KEY_PRESSED_LEFT:
        movComp->_maxVelocity.x = -0.3f;

        break;

    case KEY_PRESSED_RIGHT:
        movComp->_maxVelocity.x = 0.3f;

        break;

    case KEY_RELEASED_LEFT:
        movComp->_maxVelocity.x = 0.0f;

        break;

    case KEY_RELEASED_RIGHT:
        movComp->_maxVelocity.x = 0.0f;

        break;

    case KEY_PRESSED_SPACE:
    case KEY_PRESSED_UP:
        movComp->_isJumping = true;
        
        movComp->_maxVelocity.y = -0.9f;
        break;

    case KEY_RELEASED_SPACE:
    case KEY_RELEASED_UP:

        // To prevent further moving in the following case:
        //
        // KEY_PRESSED_RIGHT
        // 
        // >keyList: KEY_NONE, KEY_PRESSED_RIGHT;
        // 
        // KEY_PRESSED_UP
        //
        // >keyList: KEY_NONE, KEY_PRESSED_RIGHT, KEY_PRESSED_UP;
        // 
        // KEY_RELEASED_RIGHT
        // --deletion of KEY_PRESSED_RIGHT
        // >keyList: KEY_NONE, KEY_PRESSED_UP;
        //
        // KEY_RELEASED_UP
        // --deletion of KEY_PRESSED_UP and insertion of KEY_RELEASED_UP
        // >keyList: KEY_NONE, KEY_RELEASED_UP;
        //
        // Since no KEY_RELEASED_RIGHT was on the stack, hero will begin to move, cause 'movComp->_maxVelocity.x = 0.0f' was not called, so we call it here:
        
        movComp->_maxVelocity.x = 0.0f; 

        break;
    }
}
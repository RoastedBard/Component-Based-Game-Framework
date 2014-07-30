#include <iostream>
#include <memory>
#include <SDL.h>

#include "AnimationComponent.h"
#include "MovementComponent.h"
#include "GameObject.h"
#include "Enums.h"
#include "InputSystem.h"

AnimationComponent::AnimationComponent(void)
{
    _textureId = -1;
    _currentAnimation = 0;
    _isUpdateable = true;
    _id = COMPONENT_ANIMATION;
}


AnimationComponent::~AnimationComponent(void)
{
    cout<<"~Destroying AnimationComponent\n";
}

map<int, AnimationComponent::AnimationInfo> AnimationComponent::getAnimations() const
{
    return _animations;
}

AnimationComponent::AnimationInfo AnimationComponent::getAnimation(int animationId)
{
    return _animations[animationId];
}

int AnimationComponent::getTextureId() const
{
    return _textureId;
}

void AnimationComponent::setTextureId(int textureId)
{
    _textureId = textureId;
}

int AnimationComponent::getCurrentAnimationEnum() const
{
    return _currentAnimation;
}

AnimationComponent::AnimationInfo AnimationComponent::getCurrentAnimation()
{
    return _animations[_currentAnimation];
}

void AnimationComponent::setCurrentAnimation(int animationId)
{
    _currentAnimation = animationId;
}

void AnimationComponent::addAnimation(int animationId, int startframeX, int startframeY, int frameWidth, int frameHeight, int framesCount, int animationSpeed, bool horizontal, bool horizontalFlip, bool verticalFlip)
{
    if(_textureId == -1)
    {
        std::cout<<"You must specify sprite sheet for animation.\n";
        return;
    }

    AnimationInfo info;

    info.x = startframeX;
    info.y = startframeY;
    info.width = frameWidth;
    info.height = frameHeight;
    info.framesCount = framesCount;
    info.animationSpeed = animationSpeed;
    info.currentFrame = 0;
    info.horizontal = horizontal;
    info.horizontalFlip = horizontalFlip;
    info.verticalFlip = verticalFlip;

    _animations[animationId] = info;
}

void AnimationComponent::_updateAnimation()
{   
    shared_ptr<MovementComponent> movComp;

    if(_owner->hasComponent(COMPONENT_MOVEMENT))
        movComp = static_pointer_cast<MovementComponent>(_owner->getComponent(COMPONENT_MOVEMENT));

    unsigned keyPressed = InputSystem::instance()->getKeyPressed();

    switch(_currentAnimation)
    {
    case ANIMATION_STAND_LEFT:
        if(keyPressed == KEY_PRESSED_LEFT)
            _currentAnimation = ANIMATION_WALK_LEFT;

        if(keyPressed == KEY_PRESSED_RIGHT)
            _currentAnimation = ANIMATION_WALK_RIGHT;

        if(keyPressed == KEY_PRESSED_UP || keyPressed == KEY_PRESSED_SPACE)
            _currentAnimation = ANIMATION_JUMP_LEFT;

        break;

    case ANIMATION_STAND_RIGHT:
        if(keyPressed == KEY_PRESSED_LEFT)
            _currentAnimation = ANIMATION_WALK_LEFT;

        if(keyPressed == KEY_PRESSED_RIGHT)
            _currentAnimation = ANIMATION_WALK_RIGHT;

        if(keyPressed == KEY_PRESSED_UP || keyPressed == KEY_PRESSED_SPACE)
            _currentAnimation = ANIMATION_JUMP_RIGHT;

        break;

    case ANIMATION_WALK_LEFT:
        if(keyPressed == KEY_RELEASED_LEFT)
            _currentAnimation = ANIMATION_STAND_LEFT;

        if(keyPressed == KEY_PRESSED_RIGHT)
            _currentAnimation = ANIMATION_WALK_RIGHT;

        if(keyPressed == KEY_PRESSED_UP || keyPressed == KEY_PRESSED_SPACE)
            _currentAnimation = ANIMATION_JUMP_LEFT;

        break;

    case ANIMATION_WALK_RIGHT:
        if(keyPressed == KEY_RELEASED_RIGHT)
            _currentAnimation = ANIMATION_STAND_RIGHT;
        
        if(keyPressed == KEY_PRESSED_LEFT)
            _currentAnimation = ANIMATION_WALK_LEFT;
        
        if(keyPressed == KEY_PRESSED_UP || keyPressed == KEY_PRESSED_SPACE)
            _currentAnimation = ANIMATION_JUMP_RIGHT;

        break;

    case ANIMATION_JUMP_LEFT:
        if(keyPressed == KEY_PRESSED_RIGHT)
            _currentAnimation = ANIMATION_JUMP_RIGHT;

        if(movComp->_isOnTheGround)
        {
            if(_currentAnimation == ANIMATION_JUMP_LEFT)
                _currentAnimation = ANIMATION_STAND_LEFT;

            if(_currentAnimation == ANIMATION_JUMP_RIGHT)
                _currentAnimation = ANIMATION_STAND_RIGHT;
        }

        break;

    case ANIMATION_JUMP_RIGHT:
        if(keyPressed == KEY_PRESSED_LEFT)
            _currentAnimation = ANIMATION_JUMP_LEFT;

        if(movComp->_isOnTheGround)
        {
            if(_currentAnimation == ANIMATION_JUMP_LEFT)
                _currentAnimation = ANIMATION_STAND_LEFT;
        
            if(_currentAnimation == ANIMATION_JUMP_RIGHT)
                _currentAnimation = ANIMATION_STAND_RIGHT;
        }

        break;
    }
}

void AnimationComponent::update(float time)
{
    _updateAnimation();

    if(_animations.size() != 0)
    {
        if(_animations[_currentAnimation].framesCount > 1)
            _animations[_currentAnimation].currentFrame = int(( ( SDL_GetTicks() / _animations[_currentAnimation].animationSpeed) % _animations[_currentAnimation].framesCount));
    }
}


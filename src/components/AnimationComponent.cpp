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
    _id = Enums::COMPONENT_ANIMATION;
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

    _currentAnimation = animationId;
}

void AnimationComponent::_updateAnimation()
{   
    if(_animations.size() <= 1)
        return;
    
    shared_ptr<MovementComponent> movComp;

    if(_owner->hasComponent(Enums::COMPONENT_MOVEMENT))
        movComp = static_pointer_cast<MovementComponent>(_owner->getComponent(Enums::COMPONENT_MOVEMENT));

    unsigned keyPressed = InputSystem::instance()->getKeyPressed();

    switch(_currentAnimation)
    {
    case Enums::ANIMATION_STAND_LEFT:
        if(movComp->_direction == Enums::DIRECTION_LEFT)
            _currentAnimation = Enums::ANIMATION_WALK_LEFT;

        else if(movComp->_direction == Enums::DIRECTION_RIGHT)
            _currentAnimation = Enums::ANIMATION_WALK_RIGHT;

        else if(movComp->_direction == Enums::DIRECTION_UP)
            _currentAnimation = Enums::ANIMATION_JUMP_LEFT;

        break;

    case Enums::ANIMATION_STAND_RIGHT:
        if(movComp->_direction == Enums::DIRECTION_LEFT)
            _currentAnimation = Enums::ANIMATION_WALK_LEFT;

        else if(movComp->_direction == Enums::DIRECTION_RIGHT)
            _currentAnimation = Enums::ANIMATION_WALK_RIGHT;

        else if(movComp->_direction == Enums::DIRECTION_UP)
            _currentAnimation = Enums::ANIMATION_JUMP_RIGHT;

        break;

    case Enums::ANIMATION_WALK_LEFT:
        if(movComp->_direction == Enums::DIRECTION_NONE)
            _currentAnimation = Enums::ANIMATION_STAND_LEFT;

        else if(movComp->_direction == Enums::DIRECTION_RIGHT)
            _currentAnimation = Enums::ANIMATION_WALK_RIGHT;

        else if(movComp->_direction == Enums::DIRECTION_UP)
            _currentAnimation = Enums::ANIMATION_JUMP_LEFT;

        break;

    case Enums::ANIMATION_WALK_RIGHT:
        if(movComp->_direction == Enums::DIRECTION_NONE)
            _currentAnimation = Enums::ANIMATION_STAND_RIGHT;
        
        else if(movComp->_direction == Enums::DIRECTION_LEFT)
            _currentAnimation = Enums::ANIMATION_WALK_LEFT;
        
        else if(movComp->_direction == Enums::DIRECTION_UP)
            _currentAnimation = Enums::ANIMATION_JUMP_RIGHT;

        break;

    case Enums::ANIMATION_JUMP_LEFT:
        if(movComp->_direction == Enums::DIRECTION_RIGHT)
            _currentAnimation = Enums::ANIMATION_JUMP_RIGHT;

        else if(movComp->_isOnTheGround)
        {
            if(_currentAnimation == Enums::ANIMATION_JUMP_LEFT)
                _currentAnimation = Enums::ANIMATION_STAND_LEFT;

            else if(_currentAnimation == Enums::ANIMATION_JUMP_RIGHT)
                _currentAnimation = Enums::ANIMATION_STAND_RIGHT;
        }

        break;

    case Enums::ANIMATION_JUMP_RIGHT:
        if(movComp->_direction == Enums::DIRECTION_LEFT)
            _currentAnimation = Enums::ANIMATION_JUMP_LEFT;

        else if(movComp->_isOnTheGround)
        {
            if(_currentAnimation == Enums::ANIMATION_JUMP_LEFT)
                _currentAnimation = Enums::ANIMATION_STAND_LEFT;
        
            else if(_currentAnimation == Enums::ANIMATION_JUMP_RIGHT)
                _currentAnimation = Enums::ANIMATION_STAND_RIGHT;
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


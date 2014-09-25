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
    _textureId = "";
    _currentAnimation = 0;
    _isUpdateable = true;
    _id = Enums::COMPONENT_ANIMATION;

    //_script
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

string AnimationComponent::getTextureId() const
{
    return _textureId;
}

void AnimationComponent::setTextureId(string textureId)
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
    if(_textureId == "")
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

void AnimationComponent::update(float time)
{
    if(_animations.size() != 0)
    {
        if(_animations[_currentAnimation].framesCount > 1)
            _animations[_currentAnimation].currentFrame = int(( ( SDL_GetTicks() / _animations[_currentAnimation].animationSpeed) % _animations[_currentAnimation].framesCount));
    }
}


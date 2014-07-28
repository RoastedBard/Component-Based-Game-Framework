#include "AnimationComponent.h"
#include "Enums.h"
#include <iostream>
#include <SDL.h>

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

void AnimationComponent::update(float time)
{
    if(_animations.size() != 0)
    {
        if(_animations[_currentAnimation].framesCount > 1)
            _animations[_currentAnimation].currentFrame = int(( ( SDL_GetTicks() / _animations[_currentAnimation].animationSpeed) % _animations[_currentAnimation].framesCount));
    }
}


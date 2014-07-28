#include "Animation.h"
#include "TextureManager.h"

Animation::Animation(void)
{
    //_currentAnimation = ANIMATION_STAND;
}

Animation::Animation(int textureId)
{
    _textureId = textureId;
    //_currentAnimation = ANIMATION_STAND;
}

Animation::~Animation(void)
{
}

map<int, Animation::AnimationInfo> Animation::getAnimations() const
{
    return _animations;
}

Animation::AnimationInfo Animation::getAnimation(int animationId)
{
    return _animations[animationId];
}

int Animation::getTextureId() const
{
    return _textureId;
}

void Animation::setTextureId(int textureId)
{
    _textureId = textureId;
}

int  Animation::getCurrentAnimation() const
{
    return _currentAnimation;
}

void Animation::setCurrentAnimation(int animationId)
{
    _currentAnimation = animationId;
}

void Animation::addAnimation(int animationId, int startframeX, int startframeY, int frameWidth, int frameHeight, int framesCount, int animationSpeed, bool horizontal, SDL_RendererFlip flip)
{
    AnimationInfo info;

    info.x = startframeX;
    info.y = startframeY;
    info.width = frameWidth;
    info.height = frameHeight;
    info.framesCount = framesCount;
    info.animationSpeed = animationSpeed;
    info.currentFrame = 0;
    info.horizontal = horizontal;
    info.flip = flip;

    _animations[animationId] = info;
}

void Animation::updateFrame(/*int animationId*/)
{
    if(_animations[_currentAnimation].framesCount > 1)
        _animations[_currentAnimation].currentFrame = int(((SDL_GetTicks() / _animations[_currentAnimation].animationSpeed) % _animations[_currentAnimation].framesCount));
}

void Animation::playAnimation(/*int animationId,*/ int screenX, int screenY, SDL_Renderer *renderer)
{
    TextureManager::instance()->drawFrame(this, _currentAnimation, screenX, screenY, renderer);
}

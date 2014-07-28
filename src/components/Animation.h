#ifndef _ANIMATION_H_
#define _ANIMATION_H_

#include <map>
#include <SDL.h>

using namespace std;

class Animation
{
public:
    Animation(void);
    Animation(int textureId);
    ~Animation(void);

public:
    struct AnimationInfo
    {
        int x;
        int y;
        int width;
        int height;
        int framesCount;
        int animationSpeed;
        int currentFrame;
        bool horizontal;
        SDL_RendererFlip flip;
    };

public:
    map<int, Animation::AnimationInfo> getAnimations() const;
    Animation::AnimationInfo getAnimation(int animationId);
    void addAnimation(int animationId, int startframeX, int startframeY, int frameWidth, int frameHeight, int framesCount, int animationSpeed, bool horizontal, SDL_RendererFlip flip = SDL_FLIP_NONE);
    void playAnimation(/*int animationId,*/ int screenX, int screenY, SDL_Renderer *renderer);
    int getTextureId() const;
    void setTextureId(int textureId);
    void updateFrame(/*int animationId*/);
    int getCurrentAnimation() const;
    void setCurrentAnimation(int animationId);

private:
    int _textureId;
    int _currentAnimation;

private:
    map<int, Animation::AnimationInfo> _animations;
};

#endif
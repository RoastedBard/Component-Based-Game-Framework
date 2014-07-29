#ifndef _ANIMATIONCOMPONENT_H_
#define _ANIMATIONCOMPONENT_H_

#include "icomponent.h"

#include <map>

class AnimationComponent :
    public IComponent
{
public:
    AnimationComponent(void);
    ~AnimationComponent(void);

public:
    struct AnimationInfo
    {
        int x;                 // X position of the animation start frame on the sprite sheet
        int y;                 // Y position of the animation start frame on the sprite sheet
        int width;             // Width of the animation frame
        int height;            // Height of the animation frame
        int framesCount;       // Number of frames in animation
        int animationSpeed;    // Animation playback speed
        int currentFrame;      // The current frame of currently playing animation
        bool horizontal;       // Does animation frames stored horizontaly or verticaly in a sprite sheet?
        bool horizontalFlip;   // Does horizontal flipping needed? (e.g. you have only 'walking-left-animtion', and to get 'walking-right-animation' you just have to flip it horizontally, "mirror" it)
        bool verticalFlip;     // Does vertical flipping needed? (e.g. you have only 'walking-north-animtion', and to get 'walking-south-animation' you just have to flip it verticaly, "mirror" it)
    };

public:
    void addAnimation(int animationId, int startframeX, int startframeY, int frameWidth, int frameHeight, int framesCount, int animationSpeed, bool horizontal, bool horizontalFlip, bool verticalFlip);
    void setTextureId(int textureId);
    int  getTextureId() const;
    map<int, AnimationComponent::AnimationInfo> getAnimations() const;
    AnimationComponent::AnimationInfo getAnimation(int animationId);
    int getCurrentAnimationEnum() const;
    AnimationComponent::AnimationInfo getCurrentAnimation();
    void setCurrentAnimation(int animationId);
    
    virtual void update(float time);

private:
    void _updateAnimation(); // Some kind of FSM(Finite State Machine) which handling animations switching from one to another

private:
    int _textureId;             // Id of the sprite sheet where the animation is stored (sprite sheets stored somwhere else and are accessible by ID)
    int _currentAnimation;      // Current animation of the entity which has this animation component (e.g. ANIMATION_STAND, ANIMATION_RUNNING)

    map<int, AnimationInfo> _animations; // All animations of owner entity
};

#endif
#ifndef _SPRITECOMPONENT_H_
#define _SPRITECOMPONENT_H_

#include "icomponent.h"
#include <string>
#include <vector>

using namespace std;

class SpriteComponent :
    public IComponent
{
public:
    SpriteComponent(void);
    ~SpriteComponent(void);

public:
    struct SpriteInfo
    {
        int x;                 // X position of the texture on the sprite sheet
        int y;                 // Y position of the texture on the sprite sheet
        int width;             // Width of the texture frame
        int height;            // Height of the texture frame
        bool horizontalFlip;   // Does horizontal flipping needed? (e.g. you have only 'walking-left-animtion', and to get 'walking-right-animation' you just have to flip it horizontally, "mirror" it)
        bool verticalFlip;     // Does vertical flipping needed? (e.g. you have only 'walking-north-animtion', and to get 'walking-south-animation' you just have to flip it verticaly, "mirror" it)
    };

public:
    void addSprite(int frameX, int frameY, int frameWidth, int frameHeight, bool horizontalFlip, bool verticalFlip);
    void setTextureId(string textureId);
    string  getTextureId() const;
    SpriteComponent::SpriteInfo getSpriteInfo();

    virtual void update(float time){}

private:
    SpriteInfo _info;
    string _textureId;
};

#endif
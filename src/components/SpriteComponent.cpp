#include <iostream>

#include "SpriteComponent.h"
#include "Enums.h"

SpriteComponent::SpriteComponent(void)
{
    _textureId = -1;
    _id = COMPONENT_SPRITE;
}


SpriteComponent::~SpriteComponent(void)
{
}

void SpriteComponent::addSprite(int frameX, int frameY, int frameWidth, int frameHeight, bool horizontalFlip, bool verticalFlip)
{
    if(_textureId == -1)
    {
        std::cout<<"You must specify sprite sheet for texture.\n";
        return;
    }

    _info.x = frameX;
    _info.y = frameY;
    _info.width = frameWidth;
    _info.height = frameHeight;
    _info.horizontalFlip = horizontalFlip;
    _info.verticalFlip = verticalFlip;
}

int SpriteComponent::getTextureId() const
{
    return _textureId;
}

void SpriteComponent::setTextureId(int textureId)
{
    _textureId = textureId;
}

SpriteComponent::SpriteInfo SpriteComponent::getSpriteInfo()
{
    return _info;
}
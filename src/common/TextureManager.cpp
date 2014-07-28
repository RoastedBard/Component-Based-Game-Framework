#include "TextureManager.h"
#include <SDL_image.h>

std::shared_ptr<TextureManager> TextureManager::_instance = nullptr;

TextureManager::TextureManager(void)
{
}


TextureManager::~TextureManager(void)
{
}

bool TextureManager::loadTexture(std::string filename, int id, SDL_Renderer *renderer)
{
    SDL_Surface *tempSurface = IMG_Load(filename.c_str());

    if(tempSurface == 0)
    {
        return false;
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, tempSurface);

    SDL_FreeSurface(tempSurface);

    if(texture != 0)
    {
        _textureMap[id] = texture;
        return true;
    }

    return false;
}

void TextureManager::drawTexture(int id, int x, int y, int width, int height, SDL_Renderer *renderer, SDL_RendererFlip flip)
{
    SDL_Rect srcRect;
    SDL_Rect destRect;

    srcRect.x = srcRect.y = 0;
    srcRect.w = destRect.w = width;
    srcRect.h = destRect.h = height;
    destRect.x = x;
    destRect.y = y;

    SDL_RenderCopyEx(renderer, _textureMap[id], &srcRect, &destRect, 0, 0, flip);
}

void TextureManager::drawFrame(int id, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer *renderer, bool horizontal, SDL_RendererFlip flip)
{
    SDL_Rect srcRect;
    SDL_Rect destRect;

    if(currentFrame == 0)
    {

    }

    if(horizontal == true)
    {
        //if sprites placed horizontal:
        srcRect.x = width * currentFrame;
        srcRect.y = height * (currentRow - 1);
    }
    else
    {
        //if sprites placed vertical:
        srcRect.x = width * (currentRow - 1);
        srcRect.y = height * currentFrame;
    }

    srcRect.w = destRect.w = width;
    srcRect.h = destRect.h = height;

    destRect.x = x;
    destRect.y = y;

    SDL_RenderCopyEx(renderer, _textureMap[id], &srcRect, &destRect, 0, 0, flip);
}

void TextureManager::drawFrame(Animation *animation, int animationId, int screenX, int screenY, SDL_Renderer *renderer)
{
    SDL_Rect srcRect;
    SDL_Rect destRect;

    Animation::AnimationInfo info = animation->getAnimation(animationId);

    srcRect.x = info.x;
    srcRect.y = info.y;

    if(info.horizontal == true)
    {
        srcRect.x += info.currentFrame * info.width;
    }
    else if(info.horizontal == false)
    {
        srcRect.y += info.currentFrame * info.height;
    }

    srcRect.w = destRect.w = info.width;
    srcRect.h = destRect.h = info.height;

    destRect.x = screenX;
    destRect.y = screenY;

    SDL_RenderCopyEx(renderer, _textureMap[animation->getTextureId()], &srcRect, &destRect, 0, 0, info.flip);
}

std::map<int, SDL_Texture*> TextureManager::getTextureMap()
{
    return _textureMap;
}

std::shared_ptr<TextureManager> TextureManager::instance()
{
    if(_instance == nullptr)
    {
        _instance.reset(new TextureManager());
        return _instance;
    }

    return _instance;
}
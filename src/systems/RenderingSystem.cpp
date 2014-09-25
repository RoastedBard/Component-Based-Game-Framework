#include <iostream>
#include <SDL_image.h>

#include "RenderingSystem.h"
#include "Enums.h"

shared_ptr<RenderingSystem> RenderingSystem::_instance = nullptr;

RenderingSystem::RenderingSystem(void) :
    _window(nullptr, SDL_DestroyWindow),
    _renderer(nullptr, SDL_DestroyRenderer)
{
}


RenderingSystem::~RenderingSystem(void)
{
    cout<<"~Destroying RenderingSystem\n";
}

shared_ptr<RenderingSystem> RenderingSystem::instance()
{
    if(_instance == nullptr)
    {
        _instance.reset(new RenderingSystem());
        return _instance;
    }

    return _instance;
}

void RenderingSystem::addComponent(GameObject *ownerGameObject, unsigned componentType)
{
    if(componentType == Enums::COMPONENT_ANIMATION)
    {
        _animationComponents.push_back(make_shared<AnimationComponent>());
        _animationComponents.back()->setOwner(ownerGameObject);
    }
    if(componentType == Enums::COMPONENT_SPRITE)
    {
        _spriteComponents.push_back(make_shared<SpriteComponent>());
        _spriteComponents.back()->setOwner(ownerGameObject);
    }
}

shared_ptr<IComponent> RenderingSystem::getComponent(const ComponentHandle& handle)
{
    if(handle.type == Enums::COMPONENT_ANIMATION)
    {
        return _animationComponents[handle.arrayIndex];
    }
    if(handle.type == Enums::COMPONENT_SPRITE)
    {
        return _spriteComponents[handle.arrayIndex];
    }

    return nullptr;
}

std::map<string, SDL_Texture*> RenderingSystem::getTextureMap()
{
    return _textureMap;
}

unsigned RenderingSystem::getSizeOfComponentArray(unsigned type) const
{
    if(type == Enums::COMPONENT_ANIMATION)
        return _animationComponents.size();

    if(type == Enums::COMPONENT_SPRITE)
        return _spriteComponents.size();
}

bool RenderingSystem::loadTexture(std::string filename, string id)
{
    if(_textureMap.find(id) != _textureMap.end())
        return false;

    shared_ptr<SDL_Surface> tempSurface(IMG_Load(filename.c_str()), SDL_FreeSurface);

    if(tempSurface == nullptr)
    {
        return false;
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(_renderer.get(), tempSurface.get());

    if(texture != 0)
    {
        _textureMap[id] = texture;
        return true;
    }

    return false;
}

void RenderingSystem::_drawTexture(const shared_ptr<SpriteComponent>& spriteComponent)
{
    SDL_Rect srcRect;  // Rectangle area on texture to be drawn
    SDL_Rect destRect; // Rectangle area on screen to draw texture to

    //SpriteComponent::SpriteInfo info = spriteComponent->getSpriteInfo();

    srcRect.x = spriteComponent->getSpriteInfo().x;
    srcRect.y = spriteComponent->getSpriteInfo().y;
    srcRect.w = destRect.w = spriteComponent->getSpriteInfo().width;
    srcRect.h = destRect.h = spriteComponent->getSpriteInfo().height;
    destRect.x = (int)spriteComponent->getOwner()->getTranformComponent()._position.x;
    destRect.y = (int)spriteComponent->getOwner()->getTranformComponent()._position.y;
    
    // Passing 0 into the source rectangle parameter will make the renderer use the entire texture. 
    //Likewise, passing null to the destination rectangle parameter will use the entire renderer for display.
    if(spriteComponent->getSpriteInfo().horizontalFlip)
        SDL_RenderCopyEx(_renderer.get(), _textureMap[spriteComponent->getTextureId()], &srcRect, &destRect, 0, 0, SDL_FLIP_HORIZONTAL);

    else if(spriteComponent->getSpriteInfo().verticalFlip)
        SDL_RenderCopyEx(_renderer.get(), _textureMap[spriteComponent->getTextureId()], &srcRect, &destRect, 0, 0, SDL_FLIP_VERTICAL);

    else
        SDL_RenderCopyEx(_renderer.get(), _textureMap[spriteComponent->getTextureId()], &srcRect, &destRect, 0, 0, SDL_FLIP_NONE);
}

void RenderingSystem::_drawFrame(const shared_ptr<AnimationComponent>& animComponent)
{
    SDL_Rect srcRect;
    SDL_Rect destRect;

    //AnimationComponent::AnimationInfo info = animComponent->getCurrentAnimation();

    srcRect.x = animComponent->getCurrentAnimation().x;
    srcRect.y = animComponent->getCurrentAnimation().y;

    if(animComponent->getCurrentAnimation().horizontal == true)
    {
        srcRect.x += animComponent->getCurrentAnimation().currentFrame * animComponent->getCurrentAnimation().width;
    }
    else if(animComponent->getCurrentAnimation().horizontal == false)
    {
        srcRect.y += animComponent->getCurrentAnimation().currentFrame * animComponent->getCurrentAnimation().height;
    }

    srcRect.w = destRect.w = animComponent->getCurrentAnimation().width;
    srcRect.h = destRect.h = animComponent->getCurrentAnimation().height;

    destRect.x = (int)animComponent->getOwner()->getTranformComponent()._position.x;
    destRect.y = (int)animComponent->getOwner()->getTranformComponent()._position.y;

    if(animComponent->getCurrentAnimation().horizontalFlip)
        SDL_RenderCopyEx(_renderer.get(), _textureMap[animComponent->getTextureId()], &srcRect, &destRect, 0, 0, SDL_FLIP_HORIZONTAL);
    
    else if(animComponent->getCurrentAnimation().verticalFlip)
        SDL_RenderCopyEx(_renderer.get(), _textureMap[animComponent->getTextureId()], &srcRect, &destRect, 0, 0, SDL_FLIP_VERTICAL);
    
    else
        SDL_RenderCopyEx(_renderer.get(), _textureMap[animComponent->getTextureId()], &srcRect, &destRect, 0, 0, SDL_FLIP_NONE);
}

void RenderingSystem::update(float deltaTime)
{
    for(unsigned i = 0; i < _animationComponents.size(); ++i)
    {
        _animationComponents[i]->update(deltaTime);
    }
}

void RenderingSystem::render()
{
    SDL_RenderClear(_renderer.get());

    for(unsigned i = 0; i < _animationComponents.size(); ++i)
        _drawFrame(_animationComponents[i]);

    for(unsigned i = 0; i < _spriteComponents.size(); ++i)
        _drawTexture(_spriteComponents[i]);

    SDL_RenderPresent(_renderer.get());
}

void RenderingSystem::init(int windowWidth, int windowHigh, Uint32 flags)
{
    _window.reset(SDL_CreateWindow("SMBV", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHigh, flags));

    if(_window != nullptr)
    {
        std::cout << ">window creation success\n";
        _renderer.reset(SDL_CreateRenderer(_window.get(), -1, 0));
    
        if(_renderer != nullptr)
        {
            std::cout << ">renderer creation success\n";
            SDL_SetRenderDrawColor(_renderer.get(), 0, 0, 0, 255);
        }
        else
        {
            std::cout << ">renderer init fail\n";
            return;
        }
    }
    else
    {
        std::cout << ">window init fail\n";
        return;
    }

    //loadTexture("media/sprites/marioRunning.png", Enums::TEXTURE_PLAYER, _renderer.get());
    //loadTexture("media/sprites/platform.png", Enums::TEXTURE_TEST, _renderer.get());
}

void RenderingSystem::cleanup()
{
    SDL_DestroyWindow(_window.release());
    SDL_DestroyRenderer(_renderer.release());
}
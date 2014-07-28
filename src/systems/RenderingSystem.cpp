#include <iostream>
#include "RenderingSystem.h"
#include "TextureManager.h"
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
    if(componentType == COMPONENT_ANIMATION)
    {
        _animationComponents.push_back(make_shared<AnimationComponent>());
        _animationComponents.back()->setOwner(ownerGameObject);
    }
}

shared_ptr<IComponent> RenderingSystem::getComponent(const ComponentHandle& handle)
{
    if(handle.type == COMPONENT_ANIMATION)
    {
        return _animationComponents[handle.arrayIndex];
    }

    return nullptr;
}

unsigned RenderingSystem::getSizeOfComponentArray() const
{
    return _animationComponents.size();
}

void RenderingSystem::update(float deltaTime)
{
    for(int i = 0; i < _animationComponents.size(); ++i)
    {
        _animationComponents[i]->update(deltaTime);
    }
}

void RenderingSystem::drawFrame(const shared_ptr<AnimationComponent>& animComponent)
{
    SDL_Rect srcRect;
    SDL_Rect destRect;

    AnimationComponent::AnimationInfo info = animComponent->getCurrentAnimation();

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

    destRect.x = animComponent->getOwner()->getTranformComponent()._position.x;
    destRect.y = animComponent->getOwner()->getTranformComponent()._position.y;

    if(info.horizontalFlip)
        SDL_RenderCopyEx(_renderer.get(), TheTextureManager::instance()->getTextureMap()[animComponent->getTextureId()], &srcRect, &destRect, 0, 0, SDL_FLIP_HORIZONTAL);
    
    else if(info.verticalFlip)
        SDL_RenderCopyEx(_renderer.get(), TheTextureManager::instance()->getTextureMap()[animComponent->getTextureId()], &srcRect, &destRect, 0, 0, SDL_FLIP_VERTICAL);
    
    else
        SDL_RenderCopyEx(_renderer.get(), TheTextureManager::instance()->getTextureMap()[animComponent->getTextureId()], &srcRect, &destRect, 0, 0, SDL_FLIP_NONE);
}

void RenderingSystem::render()
{
    SDL_RenderClear(_renderer.get());

    for(int i = 0; i < _animationComponents.size(); ++i)
        drawFrame(_animationComponents[i]);

    SDL_RenderPresent(_renderer.get());
}

void RenderingSystem::init(int windowWidth, int windowHigh)
{
    _window.reset(SDL_CreateWindow("Hello SDL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHigh, SDL_WINDOW_SHOWN));

    if(_window != nullptr)
    {
        std::cout << ">window creation success\n";
        _renderer.reset(SDL_CreateRenderer(_window.get(), -1, 0));
    
        if(_renderer != nullptr)
        {
            std::cout << ">renderer creation success\n";
            SDL_SetRenderDrawColor(_renderer.get(), 3, 144, 255, 255);
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

    TheTextureManager::instance()->loadTexture("media/sprites/marioRunning.png", TEXTURE_PLAYER, _renderer.get());
}

void RenderingSystem::cleanup()
{
    SDL_DestroyWindow(_window.release());
    SDL_DestroyRenderer(_renderer.release());
}
#ifndef _RENDERINGSYSTEM_H_
#define _RENDERINGSYSTEM_H_

#include <SDL.h>
#include <memory>

#include "GameObject.h"
#include "AnimationComponent.h"
#include "SpriteComponent.h"
#include "ISystem.h"

using namespace std;

class RenderingSystem : public ISystem
{
public:
    RenderingSystem(void);
    ~RenderingSystem(void);

    static shared_ptr<RenderingSystem> instance();

public:
    virtual void addComponent(GameObject *ownerGameObject, unsigned componentType);
    virtual shared_ptr<IComponent> getComponent(const ComponentHandle& handle);
    virtual unsigned getSizeOfComponentArray(unsigned type) const;

public:
    void init(int windowWidth, int windowHigh, Uint32 flags);
    void render();
    void update(float deltaTime); // maybe not right to place this method in this system?
    bool loadTexture(std::string filename, string id);
    std::map<string, SDL_Texture*> getTextureMap();
    void cleanup();

private:
    void _drawFrame(const shared_ptr<AnimationComponent>& animComponent);
    void _drawTexture(const shared_ptr<SpriteComponent>& spriteComponent); // Draws entire texture on screen

private:
    unique_ptr<SDL_Window, void (*)(SDL_Window*)>     _window;
    unique_ptr<SDL_Renderer, void (*)(SDL_Renderer*)> _renderer;

    static shared_ptr<RenderingSystem>                _instance;

private:
    vector<shared_ptr<AnimationComponent>> _animationComponents;
    vector<shared_ptr<SpriteComponent>>    _spriteComponents;

    std::map<string, SDL_Texture*>            _textureMap;
};

#endif
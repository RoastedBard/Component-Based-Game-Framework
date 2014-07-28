#ifndef _RENDERINGSYSTEM_H_
#define _RENDERINGSYSTEM_H_

#include <SDL.h>
#include <memory>
#include "GameObject.h"
#include "AnimationComponent.h"
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
    unsigned getSizeOfComponentArray() const;

public:
    void init(int windowWidth, int windowHigh);
    void render();
    void update(float deltaTime); // maybe not right to place this method in this system?
    void cleanup();

private:
    void drawFrame(const shared_ptr<AnimationComponent>& animComponent);

private:
    unique_ptr<SDL_Window, void (*)(SDL_Window*)> _window;
    unique_ptr<SDL_Renderer, void (*)(SDL_Renderer*)> _renderer;

    static shared_ptr<RenderingSystem> _instance;

private:
    vector<shared_ptr<AnimationComponent>> _animationComponents;
};

#endif
#include "Game.h"
#include "InputSystem.h"
#include "Enums.h"
#include "RenderingSystem.h"
#include "PhysicsSystem.h"
#include "ScriptSystem.h"
#include "GameObjectFabric.h"
#include <iostream>

Game::Game(void)
{
    _isRunning = false;
}


Game::~Game(void)
{
}

void Game::run()
{
    _init();

    //double t = 0;
    //double dt = 1.f / 60.f;
    //double currentTime = SDL_GetTicks();

    //while(_isRunning)
    //{
    //    double newTime = SDL_GetTicks();
    //    double frameTime = newTime - currentTime;
    //    currentTime = newTime;

    //    while(frameTime > 0.0)
    //    {
    //        float deltaTime = std::min( frameTime, dt );

    //        _handleEvents();
    //        _update(deltaTime, t);
    //        
    //        frameTime -= deltaTime;
    //        t += deltaTime;
    //    }

    //    _render();
    //}

    //_cleanup();
    
    int simulaionTime = 0;

    while(_isRunning)
    {
        int realTime = SDL_GetTicks();

        while(simulaionTime < realTime)
        {
            simulaionTime += 16;
            _handleEvents();
            _update(16, 0);
        }

        _render();
    }

    _cleanup();
}

void Game::_init()
{
    if(SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        std::cout << ">SDL init success\n";

        RenderingSystem::instance()->init(800, 600);
    }
    else
    {
        std::cout << ">SDL init fail\n";
        return;
    }

    std::cout << ">init success\n";

    
    ScriptSystem::instance()->init();
    GameObjectFabric::instance()->loadGameObjects("media/scripts/GameObjects.lua");
    ScriptSystem::instance()->startScripts();

    _isRunning = true;
}

void Game::_render()
{
    RenderingSystem::instance()->render();
}

void Game::_update(float deltaTime, float time)
{
    InputSystem::instance()->update(deltaTime);
    PhysicsSystem::instance()->update(deltaTime);
    ScriptSystem::instance()->update(deltaTime);
    RenderingSystem::instance()->update(deltaTime);
}

void Game::_handleEvents()
{
    SDL_Event e;

    while(SDL_PollEvent(&e))
    {
        InputSystem::instance()->processInput(e);

        switch(e.type)
        {
        case SDL_QUIT:
            _isRunning = false;
            break;

        case SDL_KEYDOWN:
            switch(e.key.keysym.sym)
            {
                case SDLK_ESCAPE:
                    _isRunning = false;
                    break;
            }
            
            break;
        }
    }
}

void Game::_cleanup()
{
    std::cout << ">cleaning up\n";

    RenderingSystem::instance()->cleanup();

    SDL_Quit();
}

bool Game::isRunning()
{
    return _isRunning;
}
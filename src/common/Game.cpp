#include "Game.h"
#include "InputHandler.h"
#include "Enums.h"
#include "RenderingSystem.h"
#include "PhysicsSystem.h"
#include <iostream>

Game::Game(void) //:
   // _window(nullptr, SDL_DestroyWindow),
    //_renderer(nullptr, SDL_DestroyRenderer)
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

    _testGameObject.addComponent(COMPONENT_ANIMATION);
    _testGameObject.addComponent(COMPONENT_PLATFORMER_CONTROLLER);
    _testGameObject.addComponent(COMPONENT_MOVEMENT);
    _testGameObject.addComponent(COMPONENT_PLATFORMER_PHYSICS);

    _testGameObject.getTranformComponent()._position.x = 200;
    _testGameObject.getTranformComponent()._position.y = 10;

    static_pointer_cast<AnimationComponent>(_testGameObject.getComponent(COMPONENT_ANIMATION))->setTextureId(TEXTURE_PLAYER);
    static_pointer_cast<AnimationComponent>(_testGameObject.getComponent(COMPONENT_ANIMATION))->addAnimation(ANIMATION_WALK_LEFT, 0, 0, 17, 32, 3, 70, true, true, false);
    static_pointer_cast<AnimationComponent>(_testGameObject.getComponent(COMPONENT_ANIMATION))->addAnimation(ANIMATION_STAND_RIGHT, 51, 0, 17, 32, 1, 0, true, false, false);
    static_pointer_cast<AnimationComponent>(_testGameObject.getComponent(COMPONENT_ANIMATION))->addAnimation(ANIMATION_STAND_LEFT, 51, 0, 17, 32, 1, 0, true, true, false);
    static_pointer_cast<AnimationComponent>(_testGameObject.getComponent(COMPONENT_ANIMATION))->addAnimation(ANIMATION_WALK_RIGHT, 0, 0, 17, 32, 3, 70, true, false, false);
    static_pointer_cast<AnimationComponent>(_testGameObject.getComponent(COMPONENT_ANIMATION))->addAnimation(ANIMATION_JUMP_LEFT, 68, 0, 17, 32, 1, 0, true, false, false);
    static_pointer_cast<AnimationComponent>(_testGameObject.getComponent(COMPONENT_ANIMATION))->addAnimation(ANIMATION_JUMP_RIGHT, 68, 0, 17, 32, 1, 0, true, true, false);
    
    
    _isRunning = true;
}

void Game::_render()
{
    RenderingSystem::instance()->render();
}

void Game::_update(float deltaTime, float time)
{
    //_testGameObject.updateComponents(deltaTime);
    PhysicsSystem::instance()->update(deltaTime);
    RenderingSystem::instance()->update(deltaTime);
}

void Game::_handleEvents()
{
    SDL_Event e;

    if(SDL_PollEvent(&e))
    {
        switch(e.type)
        {
        case SDL_QUIT:
            _isRunning = false;
            break;

        case SDL_KEYDOWN:
            switch(e.key.keysym.sym)
            {
                case SDLK_LEFT:
                    TheInputHandler::Instance()->setKeyPressed(KEY_PRESSED_LEFT);
                    break;
                
                case SDLK_RIGHT:
                    TheInputHandler::Instance()->setKeyPressed(KEY_PRESSED_RIGHT);
                    break;
                
                case SDLK_UP:
                    TheInputHandler::Instance()->setKeyPressed(KEY_PRESSED_UP);
                    break;

                case SDLK_SPACE:
                    TheInputHandler::Instance()->setKeyPressed(KEY_PRESSED_SPACE);
                     break;

                case SDLK_ESCAPE:
                    _isRunning = false;
                    break;

                default:
                    break;
            }
            
            break;

        case SDL_KEYUP:
            if(e.key.keysym.sym == SDLK_LEFT) 
                TheInputHandler::Instance()->setKeyPressed(KEY_RELEASED_LEFT);
            
            if(e.key.keysym.sym == SDLK_RIGHT)
                TheInputHandler::Instance()->setKeyPressed(KEY_RELEASED_RIGHT);
                
            if(e.key.keysym.sym == SDLK_UP) 
                TheInputHandler::Instance()->setKeyPressed(KEY_RELEASED_UP);
            
            if(e.key.keysym.sym == SDLK_SPACE)
                TheInputHandler::Instance()->setKeyPressed(KEY_RELEASED_SPACE);
            break;
        }
    }

    //FOR DEBBUGING INPUT====================================================
    static unsigned prevKeyPress = -1;

    if(TheInputHandler::Instance()->getKeyPressed() != prevKeyPress)
    {
        switch(TheInputHandler::Instance()->getKeyPressed())
        {
        case KEY_PRESSED_LEFT:
            prevKeyPress = KEY_PRESSED_LEFT;
            cout<<"Key Pressed: KEY_PRESSED_LEFT\n";
            break;

        case KEY_PRESSED_RIGHT:
            prevKeyPress = KEY_PRESSED_RIGHT;
            cout<<"Key Pressed: KEY_PRESSED_RIGHT\n";
            break;

        case KEY_PRESSED_UP:
            prevKeyPress = KEY_PRESSED_UP;
            cout<<"Key Pressed: KEY_PRESSED_UP\n";
            break;

        case KEY_PRESSED_SPACE:
            prevKeyPress = KEY_PRESSED_SPACE;
            cout<<"Key Pressed: KEY_PRESSED_SPACE\n";
            break;

        case KEY_RELEASED_LEFT:
            prevKeyPress = KEY_RELEASED_LEFT;
            cout<<"Key Pressed: KEY_RELEASED_LEFT\n";
            break;

        case KEY_RELEASED_RIGHT:
            prevKeyPress = KEY_RELEASED_RIGHT;
            cout<<"Key Pressed: KEY_RELEASED_RIGHT\n";
            break;

        case KEY_RELEASED_UP:
            prevKeyPress = KEY_RELEASED_UP;
            cout<<"Key Pressed: KEY_RELEASED_UP\n";
            break;

        case KEY_RELEASED_SPACE:
            prevKeyPress = KEY_RELEASED_SPACE;
            cout<<"Key Pressed: KEY_RELEASED_SPACE\n";
            break;
        }
    }
    //====================================================
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
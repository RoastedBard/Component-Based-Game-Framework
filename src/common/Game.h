#ifndef _GAME_H_
#define _GAME_H_

#include <SDL.h>
#include <memory>
#include "GameObject.h"

class Game
{
public:
    Game(void);
    ~Game(void);

public:
    void run();

    bool isRunning();

private:
    void _init();
    void _render();
    void _update(float deltaTime, float time);
    void _handleEvents();
    void _cleanup();

private:
    bool _isRunning;
    GameObject _testGameObject;
    GameObject _testStaticObject;
};

#endif
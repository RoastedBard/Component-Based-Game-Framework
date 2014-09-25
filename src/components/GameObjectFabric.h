#ifndef _GAMEOBJECTFABRIC_H_
#define _GAMEOBJECTFABRIC_H_

#include <iostream>
#include <vector>
#include <memory>

#include "GameObject.h"

extern "C" 
{
    #include "lua.h"
    #include "lualib.h"
    #include "lauxlib.h"
}

#include <luabind\luabind.hpp>

using namespace luabind;
using namespace std;

class GameObjectFabric
{
public:
    GameObjectFabric(void);
    ~GameObjectFabric(void);

    static shared_ptr<GameObjectFabric> instance();

    void loadGameObjects(string filename);

private:
    void _addAnimation(const luabind::object& it, const shared_ptr<GameObject>& gObj);
    void _addSprite(const luabind::object& it, const shared_ptr<GameObject>& gObj);
    void _addTexture(const luabind::object& it, const shared_ptr<GameObject>& gObj, unsigned component);
    void _fillMovementData(const luabind::object& it, const shared_ptr<GameObject>& gObj);
    void _addScripts(const luabind::object& it, const shared_ptr<GameObject>& gObj);
    void _addCollider(const luabind::object& it, const shared_ptr<GameObject>& gObj);
private:
    vector<shared_ptr<GameObject>> _gameObjects;

    static shared_ptr<GameObjectFabric> _instance;
};

#endif
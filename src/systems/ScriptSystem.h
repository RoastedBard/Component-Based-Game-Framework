#ifndef _SCRIPTSYSTEM_H_
#define _SCRIPTSYSTEM_H_

#include <memory>
#include <vector>

#include "GameObject.h"
#include "ISystem.h"

extern "C" 
{
    #include "lua.h"
    #include "lualib.h"
    #include "lauxlib.h"
}

#include <luabind\luabind.hpp>
#include <luabind\adopt_policy.hpp>

using namespace std;
using namespace luabind;

class ScriptComponent;

class ScriptSystem : public ISystem
{
public:
    ScriptSystem(void);
    ~ScriptSystem(void);

    static shared_ptr<ScriptSystem> instance();

    void init();
    void cleanup();

    void addComponent(GameObject *ownerGameObject, unsigned componentType);

    shared_ptr<IComponent> getComponent(const ComponentHandle& handle);

    unsigned getSizeOfComponentArray(unsigned type) const;

    void update(float deltaTime);

public:
    void addGameObjectScriptSet(GameObject *gameObject);

    void startScripts();
    
    void updateScripts(float dt);

private:
    void _registerClasses();

public:
    shared_ptr<lua_State> getLuaState();
    shared_ptr<lua_State> L;

private:
    static shared_ptr<ScriptSystem> _instance;
    

    vector<shared_ptr<ScriptComponent>> _scripts;

    
};

#endif
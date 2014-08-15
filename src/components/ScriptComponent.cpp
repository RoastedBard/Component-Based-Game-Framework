#include "ScriptComponent.h"

void ScriptComponent::addScript(const char* script, GameObject* gameObject)
{
    call_function<void>(ScriptSystem::instance()->getLuaState(), "addScript", script, _owner->getIndexInGameObjectArray(), gameObject);
}

void ScriptComponent::startScriptsGameObject()
{
    lua_getglobal(ScriptSystem::instance()->getLuaState(), "startScriptsGameObject");

    lua_pushnumber(ScriptSystem::instance()->getLuaState(), _owner->getIndexInGameObjectArray());

    lua_call(ScriptSystem::instance()->getLuaState(), 1, 0);
}

void ScriptComponent::updateScriptsGameObject()
{
    lua_getglobal(ScriptSystem::instance()->getLuaState(), "updateScriptsGameObject");

    lua_pushnumber(ScriptSystem::instance()->getLuaState(), _owner->getIndexInGameObjectArray());

    lua_call(ScriptSystem::instance()->getLuaState(), 1, 0);
}

void ScriptComponent::addOwnerGameObject(char* script, GameObject* gameObject)
{
    lua_getglobal(ScriptSystem::instance()->getLuaState(), "addOwnerGameObject");

    lua_pushnumber(ScriptSystem::instance()->getLuaState(), _owner->getIndexInGameObjectArray());
    lua_pushstring(ScriptSystem::instance()->getLuaState(), script);
    lua_pushlightuserdata(ScriptSystem::instance()->getLuaState(), gameObject);
    
    lua_call(ScriptSystem::instance()->getLuaState(), 3, 0);
}

void ScriptComponent::update(float deltaTime)
{

}
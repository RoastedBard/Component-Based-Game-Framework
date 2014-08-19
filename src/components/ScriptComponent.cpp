#include "ScriptComponent.h"

void ScriptComponent::addScript(const char* script, GameObject* gameObject)
{
    call_function<void>(ScriptSystem::instance()->getLuaState().get(), "addScript", script, _owner->getIndexInGameObjectArray(), gameObject);
}

void ScriptComponent::startScriptsGameObject()
{
    lua_getglobal(ScriptSystem::instance()->getLuaState().get(), "startScriptsGameObject");

    lua_pushnumber(ScriptSystem::instance()->getLuaState().get(), _owner->getIndexInGameObjectArray());

    lua_call(ScriptSystem::instance()->getLuaState().get(), 1, 0);
}

void ScriptComponent::updateScriptsGameObject(float deltaTime)
{
    lua_getglobal(ScriptSystem::instance()->getLuaState().get(), "updateScriptsGameObject");

    lua_pushnumber(ScriptSystem::instance()->getLuaState().get(), _owner->getIndexInGameObjectArray());

    lua_pushnumber(ScriptSystem::instance()->getLuaState().get(), deltaTime);

    lua_call(ScriptSystem::instance()->getLuaState().get(), 2, 0);
}

void ScriptComponent::addOwner(char* script, GameObject* gameObject)
{
    lua_getglobal(ScriptSystem::instance()->getLuaState().get(), "addOwnerGameObject");

    lua_pushnumber(ScriptSystem::instance()->getLuaState().get(), _owner->getIndexInGameObjectArray());
    lua_pushstring(ScriptSystem::instance()->getLuaState().get(), script);
    lua_pushlightuserdata(ScriptSystem::instance()->getLuaState().get(), gameObject);
    
    lua_call(ScriptSystem::instance()->getLuaState().get(), 3, 0);
}

//void ScriptComponent::addOwner(char* script, IComponent* component, string nameInGameObjectScriptTable)
//{
//    lua_getglobal(ScriptSystem::instance()->getLuaState().get(), "addOwnerGameObject");
//
//    lua_pushstring(ScriptSystem::instance()->getLuaState().get(), nameInGameObjectScriptTable.c_str());
//    lua_pushstring(ScriptSystem::instance()->getLuaState().get(), script);
//    lua_pushlightuserdata(ScriptSystem::instance()->getLuaState().get(), component);
//    
//    lua_call(ScriptSystem::instance()->getLuaState().get(), 3, 0);
//}

void ScriptComponent::update(float deltaTime)
{

}
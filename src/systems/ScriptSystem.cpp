#include "ScriptSystem.h"
#include "ScriptComponent.h"
#include "MovementComponent.h"
#include "Enums.h"

#include <luabind/operator.hpp>

shared_ptr<ScriptSystem> ScriptSystem::_instance = nullptr;

ScriptSystem::ScriptSystem(void)
{
}


ScriptSystem::~ScriptSystem(void)
{
}

shared_ptr<ScriptSystem> ScriptSystem::instance()
{
    if(_instance == nullptr)
    {
        _instance.reset(new ScriptSystem);
        return _instance;
    }
    return _instance;   
}

void ScriptSystem::_registerClasses()
{
    module(L)
        [
            class_<IComponent>("IComponent")
                .def("getId", &IComponent::getId)
                .def("getOwner", &IComponent::getOwner)
                .def("setOwner", &IComponent::setOwner)
                .def("isUpdateable", &IComponent::isUpdateable),

            class_<TransformComponent>("TransformComponent")
                .def(constructor<>())
                .def("update", &TransformComponent::update)
                .def_readwrite("position", &TransformComponent::_position),

            class_<MovementComponent>("MovementComponent")
                .def(constructor<>())
                .def("update", &MovementComponent::update)
                .def_readwrite("velocity", &MovementComponent::_velocity)
                .def_readwrite("maxVelocity", &MovementComponent::_maxVelocity)
                .def_readwrite("isOnTheGround", &MovementComponent::_isOnTheGround)
                .def_readwrite("isJumping", &MovementComponent::_isJumping)
                .def_readwrite("direction", &MovementComponent::_direction)
                .def_readwrite("acceleration", &MovementComponent::_acceleration),

            class_<Vector2f>("Vector2f")
                .def(constructor<>())
                .def(constructor<float, float>())
                .def_readwrite("x", &Vector2f::x)
                .def_readwrite("y", &Vector2f::y)
                .def(luabind::self + luabind::other<Vector2f>())
                .def(luabind::self - luabind::other<Vector2f>())
                .def(luabind::self * float())
                .def(luabind::self / float())
                .def(luabind::self == luabind::other<Vector2f>()),
            
            class_<GameObject>("GameObject")
                .def("getIndexInGameObjectArray", &GameObject::getIndexInGameObjectArray)
                .def("getTranformComponent", &GameObject::getTranformComponent)
                .def("hasComponent", &GameObject::hasComponent)
                .def("setIndexInGameObjectArray", &GameObject::setIndexInGameObjectArray)
                .def("getComponentMovement",&GameObject::getComponentLua<MovementComponent>),

            class_<Enums>("Enums")
            .enum_("Types")
            [
                value("COMPONENT_TRANSFORM", Enums::COMPONENT_TRANSFORM),
                value("COMPONENT_MOVEMENT", Enums::COMPONENT_MOVEMENT),
                value("COMPONENT_PLATFORMER_PHYSICS", Enums::COMPONENT_PLATFORMER_PHYSICS),
                value("COMPONENT_PLATFORMER_CONTROLLER", Enums::COMPONENT_PLATFORMER_CONTROLLER),
                value("COMPONENT_ANIMATION", Enums::COMPONENT_ANIMATION),
                value("COMPONENT_SPRITE", Enums::COMPONENT_SPRITE),
                value("COMPONENT_SCRIPT", Enums::COMPONENT_SCRIPT),
    
                value("KEY_PRESSED_UP", Enums::KEY_PRESSED_UP),
                value("KEY_PRESSED_DOWN", Enums::KEY_PRESSED_DOWN),
                value("KEY_PRESSED_LEFT", Enums::KEY_PRESSED_LEFT), 
                value("KEY_PRESSED_RIGHT", Enums::KEY_PRESSED_RIGHT),
                value("KEY_PRESSED_SPACE", Enums::KEY_PRESSED_SPACE),
                value("KEY_RELEASED_LEFT", Enums::KEY_RELEASED_LEFT),
                value("KEY_RELEASED_RIGHT", Enums::KEY_RELEASED_RIGHT),
                value("KEY_RELEASED_UP", Enums::KEY_RELEASED_UP),  
                value("KEY_RELEASED_DOWN", Enums::KEY_RELEASED_DOWN),
                value("KEY_RELEASED_SPACE", Enums::KEY_RELEASED_SPACE),
                value("KEY_NONE", Enums::KEY_NONE),
    
                value("TEXTURE_PLAYER", Enums::TEXTURE_PLAYER),
                value("TEXTURE_TEST", Enums::TEXTURE_TEST),
    
                value("ANIMATION_STAND_LEFT", Enums::ANIMATION_STAND_LEFT), 
                value("ANIMATION_STAND_RIGHT", Enums::ANIMATION_STAND_RIGHT),
                value("ANIMATION_WALK_LEFT", Enums::ANIMATION_WALK_LEFT),
                value("ANIMATION_WALK_RIGHT", Enums::ANIMATION_WALK_RIGHT),
                value("ANIMATION_JUMP_LEFT", Enums::ANIMATION_JUMP_LEFT),
                value("ANIMATION_JUMP_RIGHT", Enums::ANIMATION_JUMP_RIGHT),

                value("DIRECTION_LEFT", Enums::DIRECTION_LEFT), 
                value("DIRECTION_RIGHT", Enums::DIRECTION_RIGHT),
                value("DIRECTION_UP", Enums::DIRECTION_UP),
                value("DIRECTION_NONE", Enums::DIRECTION_NONE)
            ]
        ];
}

void ScriptSystem::init()
{
    L = luaL_newstate();
    luaL_openlibs(L);
    open(L);

    _registerClasses();

    luaL_dofile(ScriptSystem::instance()->getLuaState(), "media/scripts/ScriptManager.lua");
}

void ScriptSystem::cleanup()
{
    lua_close(L);
}

void ScriptSystem::addComponent(GameObject *ownerGameObject, unsigned componentType)
{
    _scripts.push_back(make_shared<ScriptComponent>());
    _scripts.back()->setOwner(ownerGameObject);

    addGameObjectScriptSet(ownerGameObject);
}

shared_ptr<IComponent> ScriptSystem::getComponent(const ComponentHandle& handle)
{
    return _scripts[handle.arrayIndex];
}

unsigned ScriptSystem::getSizeOfComponentArray(unsigned type) const
{
    return _scripts.size();
}

void ScriptSystem::update(float deltaTime)
{
    //luaL_dofile(L, "media/scripts/EnemyPatrollingScript.lua");
    updateScripts(deltaTime);
}

void ScriptSystem::addGameObjectScriptSet(GameObject *gameObject)
{
    lua_getglobal(L, "addGameObjectScriptSet");

    lua_pushnumber(L, gameObject->getIndexInGameObjectArray());

    lua_call(L, 1, 0); 
}

void ScriptSystem::startScripts()
{
    lua_getglobal(L, "startScripts");

    lua_call(L, 0, 0);
}

void ScriptSystem::updateScripts(float dt)
{
    lua_getglobal(L, "updateScripts");

    lua_pushnumber(L, dt);

    lua_call(L, 1, 0);
}

lua_State* ScriptSystem::getLuaState()
{
    return L;
}
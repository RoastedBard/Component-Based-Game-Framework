#include "GameObjectFabric.h"
#include "AnimationComponent.h"
#include "MovementComponent.h"
#include "ScriptSystem.h"
#include "ScriptComponent.h"
#include "SpriteComponent.h"
#include "Enums.h"

shared_ptr<GameObjectFabric> GameObjectFabric::_instance = nullptr;

GameObjectFabric::GameObjectFabric(void)
{

}

GameObjectFabric::~GameObjectFabric(void)
{

}

shared_ptr<GameObjectFabric> GameObjectFabric::instance()
{
    if(_instance == nullptr)
    {
        _instance.reset(new GameObjectFabric);
        return _instance;
    }

    return _instance;
}

void GameObjectFabric::_addSprite(const luabind::object& it, const shared_ptr<GameObject>& gObj)
{
    static_pointer_cast<SpriteComponent>(gObj->getComponent(Enums::COMPONENT_SPRITE))->addSprite(object_cast<int>(it["sprite"][1]), object_cast<int>(it["sprite"][2]),
                                                                                                 object_cast<int>(it["sprite"][3]), object_cast<int>(it["sprite"][4]),
                                                                                                 object_cast<int>(it["sprite"][5]), object_cast<int>(it["sprite"][6]));
}

void GameObjectFabric::_addAnimation(const luabind::object& it, const shared_ptr<GameObject>& gObj)
{
    //string script = object_cast<string>(it["animationScript"]);

    //static_pointer_cast<AnimationComponent>(gObj->getComponent(Enums::COMPONENT_ANIMATION))->setScript(script);

    for(luabind::iterator z(it["animations"]), end; z != end; ++z)
    {
        object zz = object_cast<object>(*z);

        static_pointer_cast<AnimationComponent>(gObj->getComponent(Enums::COMPONENT_ANIMATION))->addAnimation(object_cast<int>(zz[1]), object_cast<int>(zz[2]), 
                                                                                                             object_cast<int>(zz[3]), object_cast<int>(zz[4]), 
                                                                                                             object_cast<int>(zz[5]), object_cast<int>(zz[6]), 
                                                                                                             object_cast<int>(zz[7]), object_cast<int>(zz[8]), 
                                                                                                             object_cast<int>(zz[9]), object_cast<int>(zz[10]));            
    }
}

void GameObjectFabric::_addTexture(const luabind::object& it, const shared_ptr<GameObject>& gObj, unsigned component)
{
    unsigned texId = object_cast<unsigned>(it["textures"]["textureId"]);

    if(component == Enums::COMPONENT_ANIMATION)
        static_pointer_cast<AnimationComponent>(gObj->getComponent(Enums::COMPONENT_ANIMATION))->setTextureId(texId);
    else if(component == Enums::COMPONENT_SPRITE)
        static_pointer_cast<SpriteComponent>(gObj->getComponent(Enums::COMPONENT_SPRITE))->setTextureId(texId);
}

void GameObjectFabric::_fillMovementData(const luabind::object& it, const shared_ptr<GameObject>& gObj)
{
    static_pointer_cast<MovementComponent>(gObj->getComponent(Enums::COMPONENT_MOVEMENT))->_velocity.x = object_cast<float>(it["movement"]["velocityX"]);
    static_pointer_cast<MovementComponent>(gObj->getComponent(Enums::COMPONENT_MOVEMENT))->_velocity.y = object_cast<float>(it["movement"]["velocityY"]);
    static_pointer_cast<MovementComponent>(gObj->getComponent(Enums::COMPONENT_MOVEMENT))->_acceleration.x = object_cast<float>(it["movement"]["accelerationX"]);
    static_pointer_cast<MovementComponent>(gObj->getComponent(Enums::COMPONENT_MOVEMENT))->_acceleration.y = object_cast<float>(it["movement"]["accelerationy"]);
    static_pointer_cast<MovementComponent>(gObj->getComponent(Enums::COMPONENT_MOVEMENT))->_maxVelocity.x = object_cast<float>(it["movement"]["maxVelocityX"]);
    static_pointer_cast<MovementComponent>(gObj->getComponent(Enums::COMPONENT_MOVEMENT))->_maxVelocity.y = object_cast<float>(it["movement"]["maxVelocityY"]);
    static_pointer_cast<MovementComponent>(gObj->getComponent(Enums::COMPONENT_MOVEMENT))->_direction = object_cast<int>(it["movement"]["direction"]);
    static_pointer_cast<MovementComponent>(gObj->getComponent(Enums::COMPONENT_MOVEMENT))->_isJumping = object_cast<int>(it["movement"]["isJumping"]);
    static_pointer_cast<MovementComponent>(gObj->getComponent(Enums::COMPONENT_MOVEMENT))->_isOnTheGround = object_cast<int>(it["movement"]["isOnTheGround"]);
}

void GameObjectFabric::_addScripts(const luabind::object& it, const shared_ptr<GameObject>& gObj)
{
    for(luabind::iterator i(it["scripts"]), end; i != end; ++i)
    {
        string fullPath = object_cast<string>(*i);

        luaL_dofile(ScriptSystem::instance()->getLuaState().get(), fullPath.c_str());

        string name;

        for(string::iterator i = fullPath.end() - 1; *i != '/'; --i)
            name += *i;

        reverse(name.begin(), name.end());

        name.erase(name.find('.'), name.size());

        static_pointer_cast<ScriptComponent>(gObj->getComponent(Enums::COMPONENT_SCRIPT))->addScript(name.c_str(), gObj.get());
    }
}

void GameObjectFabric::loadGameObjects(string filename)
{
    luaL_dofile(ScriptSystem::instance()->getLuaState().get(), filename.c_str());

    unsigned index = 1;

    try
    {
        // Looping through every game object:
        for(luabind::iterator i(globals(ScriptSystem::instance()->getLuaState().get())["GameObjects"]), end; i != end; ++i)
        {
            _gameObjects.push_back(make_shared<GameObject>());
            

            object ii = object_cast<object>(*i);

            // Retrieving coordinates:
            _gameObjects.back()->getTranformComponent()._position.x = object_cast<int>(ii["posX"]);
            _gameObjects.back()->getTranformComponent()._position.y = object_cast<int>(ii["posY"]);

            // Retrieving components:
            for(luabind::iterator j(ii["components"]), end; j != end; ++j)
            {
                unsigned type = object_cast<unsigned>(*j);

                switch(type)
                {
                case Enums::COMPONENT_ANIMATION:
                    _gameObjects.back()->addComponent(type);

                    _addTexture(ii, _gameObjects.back(), type);   // Retrieving texture id
                    _addAnimation(ii, _gameObjects.back()); // Retrieving animations

                    break;
                
                case Enums::COMPONENT_PLATFORMER_CONTROLLER:
                    _gameObjects.back()->addComponent(type);
                    
                    break;
                
                case Enums::COMPONENT_MOVEMENT:
                    _gameObjects.back()->addComponent(type);

                    _fillMovementData(ii, _gameObjects.back());
                    break;
                
                case Enums::COMPONENT_PLATFORMER_PHYSICS:
                    _gameObjects.back()->addComponent(type);
                    break;
                
                case Enums::COMPONENT_SPRITE:
                    _gameObjects.back()->addComponent(type);

                    _addTexture(ii, _gameObjects.back(), type);
                    _addSprite(ii, _gameObjects.back());
                    
                    break;

                case Enums::COMPONENT_SCRIPT:
                    _gameObjects.back()->setIndexInGameObjectArray(index);

                    _gameObjects.back()->addComponent(type);
                    

                    _addScripts(ii, _gameObjects.back());

                    ++index;
                default:
                    break;
                }
            }

            
        }
    }
    catch(const exception &TheError)
    {
        cerr << TheError.what() << endl;
    }
}
#include "InputSystem.h"
#include "Enums.h"

shared_ptr<InputSystem> InputSystem::_instance = nullptr;

InputSystem::InputSystem(void)
{
    _keyList.push_back(Enums::KEY_NONE);
}

InputSystem::~InputSystem(void)
{
}

shared_ptr<InputSystem> InputSystem::instance()
{
    if(_instance == nullptr)
    {
        _instance.reset(new InputSystem());
        return _instance;
    }

    return _instance;
}

void InputSystem::addComponent(GameObject *ownerGameObject, unsigned componentType)
{
    switch(componentType)
    {
    case Enums::COMPONENT_PLATFORMER_CONTROLLER:
        _platformerControllers.push_back(make_shared<PlatformerController>());
        _platformerControllers.back()->setOwner(ownerGameObject);
        break;
    }
}

shared_ptr<IComponent> InputSystem::getComponent(const ComponentHandle& handle)
{
    switch(handle.type)
    {
    case Enums::COMPONENT_PLATFORMER_CONTROLLER:
        return _platformerControllers[handle.arrayIndex];

    default:
        return nullptr;
    }
}

unsigned InputSystem::getSizeOfComponentArray(unsigned type) const
{
    return _platformerControllers.size();
}

list<unsigned>& InputSystem::getKeyList()
{
    return _keyList;
}

unsigned InputSystem::getKeyPressed()
{
    return _keyList.back();
}

void InputSystem::processInput(SDL_Event &e)
{
    unsigned keyReleased = Enums::KEY_NONE;
    unsigned keyPressed = Enums::KEY_NONE;

    switch(e.type)
    {
        case SDL_KEYDOWN:
            switch(e.key.keysym.sym)
            {
                case SDLK_LEFT:
                    keyPressed = Enums::KEY_PRESSED_LEFT;

                    break;
                
                case SDLK_RIGHT:
                    keyPressed = Enums::KEY_PRESSED_RIGHT;

                    break;
                
                case SDLK_UP:
                    keyPressed = Enums::KEY_PRESSED_UP;

                    break;

                case SDLK_SPACE:
                    keyPressed = Enums::KEY_PRESSED_SPACE;

                     break;
            }

            if(_keyList.back() != keyPressed)
                _keyList.push_back(keyPressed);

            break;

        case SDL_KEYUP:
            switch(e.key.keysym.sym)
            {
                case SDLK_LEFT:
                    keyReleased = Enums::KEY_RELEASED_LEFT;

                    _deleteValueFromKeyList(Enums::KEY_PRESSED_LEFT);

                    break;
                
                case SDLK_RIGHT:
                    keyReleased = Enums::KEY_RELEASED_RIGHT;

                    _deleteValueFromKeyList(Enums::KEY_PRESSED_RIGHT);

                    break;
                
                case SDLK_UP:
                    keyReleased = Enums::KEY_RELEASED_UP;

                    _deleteValueFromKeyList(Enums::KEY_PRESSED_UP);

                    break;

                case SDLK_SPACE:
                    keyReleased = Enums::KEY_RELEASED_SPACE;

                    _deleteValueFromKeyList(Enums::KEY_PRESSED_SPACE);

                     break;
            }

            if(_keyList.back() == Enums::KEY_RELEASED_LEFT ||
               _keyList.back() == Enums::KEY_RELEASED_RIGHT ||
               _keyList.back() == Enums::KEY_RELEASED_UP ||
               _keyList.back() == Enums::KEY_RELEASED_SPACE)
                        _keyList.pop_back();

            if(_keyList.back() == Enums::KEY_NONE && keyReleased != Enums::KEY_NONE)
                _keyList.push_back(keyReleased);

            break;
    }

}

void InputSystem::update(float deltaTime)
{
    for(unsigned i = 0; i < _platformerControllers.size(); ++i)
        _platformerControllers[i]->update(deltaTime);
}

void InputSystem::_deleteValueFromKeyList(unsigned key)
{
    if(_keyList.back() != key)
    {
        for(list<unsigned>::iterator i = _keyList.begin(); i != _keyList.end(); ++i)
        {
            if(*i == key)
            {
                _keyList.erase(i);
                break;
            }
        }
    }
    else
        _keyList.pop_back();
}
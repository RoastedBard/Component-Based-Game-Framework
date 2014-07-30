#include "InputSystem.h"
#include "Enums.h"

shared_ptr<InputSystem> InputSystem::_instance = nullptr;

InputSystem::InputSystem(void)
{
    _keyList.push_back(KEY_NONE);
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
    case COMPONENT_PLATFORMER_CONTROLLER:
        _platformerControllers.push_back(make_shared<PlatformerController>());
        _platformerControllers.back()->setOwner(ownerGameObject);
        break;
    }
}

shared_ptr<IComponent> InputSystem::getComponent(const ComponentHandle& handle)
{
    switch(handle.type)
    {
    case COMPONENT_PLATFORMER_CONTROLLER:
        return _platformerControllers[handle.arrayIndex];

    default:
        return nullptr;
    }
}

unsigned InputSystem::getSizeOfComponentArray() const
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

void InputSystem::processInput(SDL_Event e)
{
    unsigned keyReleased = KEY_NONE;
    unsigned keyPressed = KEY_NONE;

    switch(e.type)
    {
        case SDL_KEYDOWN:
            switch(e.key.keysym.sym)
            {
                case SDLK_LEFT:
                    keyPressed = KEY_PRESSED_LEFT;

                    break;
                
                case SDLK_RIGHT:
                    keyPressed = KEY_PRESSED_RIGHT;

                    break;
                
                case SDLK_UP:
                    keyPressed = KEY_PRESSED_UP;

                    break;

                case SDLK_SPACE:
                    keyPressed = KEY_PRESSED_SPACE;

                     break;
            }

            if(_keyList.back() != keyPressed)
                _keyList.push_back(keyPressed);

            break;

        case SDL_KEYUP:
            switch(e.key.keysym.sym)
            {
                case SDLK_LEFT:
                    keyReleased = KEY_RELEASED_LEFT;

                    _deleteValueFromKeyList(KEY_PRESSED_LEFT);

                    break;
                
                case SDLK_RIGHT:
                    keyReleased = KEY_RELEASED_RIGHT;

                    _deleteValueFromKeyList(KEY_PRESSED_RIGHT);

                    break;
                
                case SDLK_UP:
                    keyReleased = KEY_RELEASED_UP;

                    _deleteValueFromKeyList(KEY_PRESSED_UP);

                    break;

                case SDLK_SPACE:
                    keyReleased = KEY_RELEASED_SPACE;

                    _deleteValueFromKeyList(KEY_PRESSED_SPACE);

                     break;
            }

            if(_keyList.back() == KEY_RELEASED_LEFT ||
               _keyList.back() == KEY_RELEASED_RIGHT ||
               _keyList.back() == KEY_RELEASED_UP ||
               _keyList.back() == KEY_RELEASED_SPACE)
                        _keyList.pop_back();

            if(_keyList.back() == KEY_NONE && keyReleased != KEY_NONE)
                _keyList.push_back(keyReleased);

            break;
    }

}

void InputSystem::update(float deltaTime)
{
    for(size_t i = 0; i < _platformerControllers.size(); ++i)
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
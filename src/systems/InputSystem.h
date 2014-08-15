#ifndef _INPUTSYSTEM_H_
#define _INPUTSYSTEM_H_

#include <vector>
#include <list>
#include <SDL.h>

#include "isystem.h"
#include "PlatformerController.h"

using namespace std;

class InputSystem :
    public ISystem
{
public:
    InputSystem(void);
    ~InputSystem(void);

    static shared_ptr<InputSystem> instance();

public:
    virtual void addComponent(GameObject *ownerGameObject, unsigned componentType);
    virtual shared_ptr<IComponent> getComponent(const ComponentHandle& handle);
    virtual unsigned getSizeOfComponentArray(unsigned type) const;

public:
    void processInput(SDL_Event &e);

    void update(float deltaTime);

    list<unsigned>& getKeyList();

    unsigned getKeyPressed();

private:
    void _deleteValueFromKeyList(unsigned key); //deletes Enums::KEY_PRESSED_ value from keylist when corresponding key is released

private:
    vector<shared_ptr<PlatformerController>> _platformerControllers;

    list<unsigned>                           _keyList;

    static shared_ptr<InputSystem>           _instance;
};

#endif
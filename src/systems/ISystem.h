#ifndef _ISYSTEM_H_
#define _ISYSTEM_H_

#include <memory>

#include "IComponent.h"
#include "ComponentHandle.h"

using namespace std;

class GameObject;

class ISystem
{
public:
    virtual ~ISystem(void){}

public:
    virtual void addComponent(GameObject *ownerGameObject, unsigned componentType) = 0;
    virtual shared_ptr<IComponent> getComponent(const ComponentHandle& handle) = 0;
};

#endif
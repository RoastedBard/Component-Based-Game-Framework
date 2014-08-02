#ifndef _COMPONENTFABRIC_H_
#define _COMPONENTFABRIC_H_

#include <memory>
#include "ISystem.h"
#include "ComponentHandle.h"
#include "IComponent.h"

using namespace std;

class GameObject;

class ComponentFabric
{
public:
    ComponentFabric(void);
    ~ComponentFabric(void);

    static shared_ptr<ComponentFabric> instance();

public:
    ComponentHandle addComponent(GameObject *ownerGameObject, unsigned type); // creates a new object, and returns a handle(index in a corresponding component aray)
    shared_ptr<IComponent> getComponent(ComponentHandle handle);

private:
    ComponentHandle _addComponent(unsigned type, GameObject *ownerGameObject, shared_ptr<ISystem> system);

private:
    static shared_ptr<ComponentFabric> _instance;
};

#endif
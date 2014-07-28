#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_

#include <vector>

#include "ComponentHandle.h"
#include "IComponent.h"
#include "TransformComponent.h"

using namespace std;

class GameObject
{
public:
    GameObject();
    ~GameObject();

public:
    shared_ptr<IComponent> getComponent(unsigned id);
    void addComponent(unsigned type);
    void updateComponents(float deltaTime); // Maybe not the best idea
    bool hasComponent(unsigned type) const;
    TransformComponent& getTranformComponent();

private:
    vector<ComponentHandle> _componentArray;
    TransformComponent _transformComponent;

};

#endif
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
    void setIndexInGameObjectArray(unsigned index);
    unsigned getIndexInGameObjectArray() const;

    template<class T>
    T* getComponentLua(int type);

private:
    vector<ComponentHandle> _componentArray;
    TransformComponent _transformComponent;
    unsigned _indexInGameObjectArray;

};

template<class T>
T* GameObject::getComponentLua(int type)
{
    switch(type)
    {
        case Enums::COMPONENT_TRANSFORM:
            return static_cast<T*>(this->getComponent(Enums::COMPONENT_TRANSFORM).get());
        break;
        
        case Enums::COMPONENT_MOVEMENT:
            return static_cast<T*>(this->getComponent(Enums::COMPONENT_MOVEMENT).get());
        break;

        case Enums::COMPONENT_ANIMATION:
            return static_cast<T*>(this->getComponent(Enums::COMPONENT_ANIMATION).get());
        break;

        case Enums::COMPONENT_COLLIDER:
            return static_cast<T*>(this->getComponent(Enums::COMPONENT_COLLIDER).get());
        break;
    }
}

#endif
#ifndef _ICOMPONENT_H_
#define _ICOMPONENT_H_

#include <memory>

using namespace std;

class GameObject;

class IComponent
{
public:
    IComponent(void);
    virtual ~IComponent(void);

public:
    virtual void update(float deltaTime) = 0;
    unsigned getId() const;
    void setOwner(GameObject *owner);
    GameObject* getOwner();
    bool isUpdateable() const;

protected:
    unsigned _id; // Predefined enum value. for example: Enums::COMPONENT_TRANSFORM, Enums::COMPONENT_PLATFORMER_CONTROLLER, etc.
    unique_ptr<GameObject> _owner; // GameObject that owns this component
    bool _isUpdateable; //Does this component needs to be updated constantly?
};

#endif
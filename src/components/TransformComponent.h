#ifndef _TRANSFORMCOMPONENT_H_
#define _TRANSFORMCOMPONENT_H_

#include "icomponent.h"
#include "Vector2.h"

class TransformComponent :
    public IComponent
{
public:
    TransformComponent(void);
    ~TransformComponent(void);

public:
    virtual void update(float deltaTime);

public:
    Vector2f _position;
};

#endif
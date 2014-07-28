#ifndef _MOVEMENTCOMPONENT_H_
#define _MOVEMENTCOMPONENT_H_

#include "icomponent.h"
#include "Vector2.h"

class MovementComponent :
    public IComponent
{
public:
    MovementComponent(void);
    ~MovementComponent(void);

public:
    virtual void update(float deltaTime);

public:
    Vector2f _velocity;
    Vector2f _acceleration;
    
    Vector2f _maxVelocity;
    bool     _isJumping;
    bool  _isOnTheGround;

    bool _isMovingHorizontal;
};

#endif
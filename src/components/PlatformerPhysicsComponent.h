#ifndef _PLATFORMERPHYSICSCOMPONENT_H_
#define _PLATFORMERPHYSICSCOMPONENT_H_

#include "icomponent.h"
#include "MovementComponent.h"

class PlatformerPhysicsComponent :
    public IComponent
{
public:
    PlatformerPhysicsComponent(void);
    ~PlatformerPhysicsComponent(void);

public:
    virtual void update(float deltaTime);

private:
    void _performGravity(float deltaTime);
    void _performMovement(float deltaTime);
    void _performJumping(float deltaTime);
    float _lerp(float max, float current, float acceleration);

private:
    Vector2f _gravity;
    //float _gravity;

    shared_ptr<MovementComponent> movComp;
};

#endif
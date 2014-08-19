#ifndef _PLATFORMERCONTROLLER_H_
#define _PLATFORMERCONTROLLER_H_

#include "icomponent.h"
#include "MovementComponent.h"

class PlatformerController :
    public IComponent
{
public:
    PlatformerController(void);
    ~PlatformerController(void);

public:
    virtual void update(float deltaTime);

private:
    shared_ptr<MovementComponent> _movComp;
};

#endif
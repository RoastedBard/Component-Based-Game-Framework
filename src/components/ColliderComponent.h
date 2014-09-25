#ifndef _COLLIDERCOMPONENT_H_
#define _COLLIDERCOMPONENT_H_

#include "icomponent.h"
#include "Vector2.h"
#include <Box2D\Box2D.h>

class ColliderComponent :
    public IComponent
{
public:
    ColliderComponent(void);
    ColliderComponent(int minX, int minY, int width, int height);
    ~ColliderComponent(void);

public:
    virtual void update(float deltaTime);

public:
    bool checkCollision(shared_ptr<ColliderComponent> other);

    void setupCollider(int minX, int minY, int width, int height);
    void setupFootSensor(bool isHaveFootSensor);

    Vector2i& getMin();
    Vector2i& getMax();
    Vector2i& getCenter();
    Vector2i& getSize();

    unsigned& getCollisionCount();

    bool isHaveFootSensor();
    shared_ptr<ColliderComponent> getFootSensor();
    void setIsCollided(bool isCollided);
    bool getIsCollided();

private:
    Vector2i _min;
    Vector2i _max;

    Vector2i _center;

    Vector2i _size;

    bool _isCollided;
    unsigned _collisionCount;
    shared_ptr<ColliderComponent> _collidedWithFootSensor;
    shared_ptr<ColliderComponent> _footSensor;
    bool _isHaveFootSensor;
};

#endif
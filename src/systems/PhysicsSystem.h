#ifndef _PHYSICSSYSTEM_H_
#define _PHYSICSSYSTEM_H_

#include "isystem.h"
#include "PlatformerController.h"
#include "MovementComponent.h"
#include "PlatformerPhysicsComponent.h"
#include "ColliderComponent.h"
#include <memory>
#include <vector>

using namespace std;

struct DynamicBody
{
    float w;
    float h;
    b2BodyDef bodyDef;
    b2PolygonShape shape;
    b2Body* body;
    b2FixtureDef fixtureDef;
};

struct StaticBody
{
    float w;
    float h;
    b2BodyDef bodyDef;
    b2PolygonShape shape;
    b2Body* body;
};

class PhysicsSystem :
    public ISystem
{
public:
    PhysicsSystem(void);
    ~PhysicsSystem(void);

    static shared_ptr<PhysicsSystem> instance();

public:
    virtual void addComponent(GameObject *ownerGameObject, unsigned componentType);
    virtual shared_ptr<IComponent> getComponent(const ComponentHandle& handle);

    virtual unsigned getSizeOfComponentArray(unsigned type) const;
    void update(float deltaTime);

    void checkCollision();
    bool isCollided(shared_ptr<ColliderComponent> colliderA, shared_ptr<ColliderComponent> colliderB);

    void addBody(int x, int y, int width, int height, unsigned type);

private:
    vector<shared_ptr<MovementComponent>>              _movementComponents;
    vector<shared_ptr<PlatformerPhysicsComponent>>     _physicsComponents;
    vector<shared_ptr<ColliderComponent>>              _colliderComponents;

    vector<StaticBody> staticBodies;
    vector<DynamicBody> dynamicBodies;

    static shared_ptr<PhysicsSystem> _instance;
};

#endif
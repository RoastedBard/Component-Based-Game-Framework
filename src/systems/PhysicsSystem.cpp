#include <iostream>
#include "PhysicsSystem.h"
#include "Enums.h"

shared_ptr<PhysicsSystem> PhysicsSystem::_instance = nullptr;

PhysicsSystem::PhysicsSystem(void)
{
}

PhysicsSystem::~PhysicsSystem(void)
{
    cout<<"~Destroying PhysicsSystem\n";
}

shared_ptr<PhysicsSystem> PhysicsSystem::instance()
{
    if(_instance == nullptr)
    {
        _instance.reset(new PhysicsSystem());
        return _instance;
    }

    return _instance;
}

void PhysicsSystem::checkCollision()
{
    
    //for(unsigned i = 0; i < _colliderComponents.size(); ++i)
    //{
        for(unsigned j = 0; j < _colliderComponents.size(); ++j)
        {
            
            if(j != 0)
            {
                bool collision = _colliderComponents[0]->checkCollision(_colliderComponents[j]);

                if(collision)
                {
                    _colliderComponents[0]->setIsCollided(true);
                    //_colliderComponents[j]->getCollisionCount()++;
                }
                //if(isCollided(_colliderComponents[0], _colliderComponents[j]))
                //{
                //    //cout<<">Collision occured\n"; // TESTING ONLY
                //    _colliderComponents[i]->setIsCollided(true);
                //    
                //}
                //else
                //{
                //    //if( _colliderComponents[i]->getIsCollided() != false) // TESTING ONLY
                //        //cout<<">Collision dismissed\n"; // TESTING ONLY
                //    _colliderComponents[i]->setIsCollided(false);
                //}
            }
        //}
    }
}

bool PhysicsSystem::isCollided(shared_ptr<ColliderComponent> colliderA, shared_ptr<ColliderComponent> colliderB)
{
    Vector2i dist = colliderA->getCenter() - colliderB->getCenter();

    if(abs(dist.x) > (colliderA->getSize().x / 2) + (colliderB->getSize().x / 2) || abs(dist.y) > (colliderA->getSize().y / 2) + (colliderB->getSize().y/ 2))
        return false;

    return true;

    //// Exit with no intersection if separated along an axis
    //if (colliderA->getMax().x < colliderB->getMin().x || colliderA->getMin().x > colliderB->getMax().x) return false;
    //if (colliderA->getMax().y < colliderB->getMin().y || colliderA->getMin().y > colliderB->getMax().y) return false;

    //// Overlapping on all axes means AABBs are intersecting
    //return true;

 //   float Tx = abs( ((colliderA->getMin().x + colliderA->getMax().x) / 2) - ((colliderB->getMin().x + colliderB->getMax().x) / 2) );
	//float Ty = abs( ((colliderA->getMin().y + colliderA->getMax().y) / 2) - ((colliderB->getMin().y + colliderB->getMax().y) / 2) );

	//float Ax = abs((colliderA->getMax().x - colliderA->getMin().x) / 2);
	//float Ay = abs((colliderA->getMin().y - colliderA->getMax().y) / 2);

	//float Bx = abs((colliderB->getMax().x - colliderB->getMin().x) / 2);
	//float By = abs((colliderA->getMin().y - colliderB->getMax().y) / 2);

	//if(Tx >= Ax + Bx || Ty >= Ay + By)
	//	return false;

	//return true;
}

void PhysicsSystem::addBody(int x, int y, int width, int height, unsigned type)
{
    
}

void PhysicsSystem::update(float deltaTime)
{
    checkCollision();

    for(unsigned i = 0; i < _colliderComponents.size(); ++i)
        _colliderComponents[i]->update(deltaTime);

    for(unsigned i = 0; i < _physicsComponents.size(); ++i)
        _physicsComponents[i]->update(deltaTime);

    
}

unsigned PhysicsSystem::getSizeOfComponentArray(unsigned type) const
{
    switch(type)
    {
    case Enums::COMPONENT_MOVEMENT:
        return _movementComponents.size();

    case Enums::COMPONENT_PLATFORMER_PHYSICS:
        return _physicsComponents.size();

    case Enums::COMPONENT_COLLIDER:
        return _colliderComponents.size();
    }
}

void PhysicsSystem::addComponent(GameObject *ownerGameObject, unsigned componentType)
{
    switch(componentType)
    {
    case Enums::COMPONENT_MOVEMENT:
        _movementComponents.push_back(make_shared<MovementComponent>());
        _movementComponents.back()->setOwner(ownerGameObject);
        break;

    case Enums::COMPONENT_PLATFORMER_PHYSICS:
        _physicsComponents.push_back(make_shared<PlatformerPhysicsComponent>());
        _physicsComponents.back()->setOwner(ownerGameObject);
        break;

    case Enums::COMPONENT_COLLIDER:
        _colliderComponents.push_back(make_shared<ColliderComponent>());
        _colliderComponents.back()->setOwner(ownerGameObject);
        break;
    }
}

shared_ptr<IComponent> PhysicsSystem::getComponent(const ComponentHandle& handle)
{
    switch(handle.type)
    {
    case Enums::COMPONENT_MOVEMENT:
        return _movementComponents[handle.arrayIndex];

    case Enums::COMPONENT_PLATFORMER_PHYSICS:
        return _physicsComponents[handle.arrayIndex];

    case Enums::COMPONENT_COLLIDER:
        return _colliderComponents[handle.arrayIndex];

    default:
        return nullptr;
    }
}
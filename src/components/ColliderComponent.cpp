#include "ColliderComponent.h"
#include "GameObject.h"
#include <iostream>

ColliderComponent::ColliderComponent(void)
{
    _isCollided = false;
    _isHaveFootSensor = false;
    _collisionCount = 0;
}

ColliderComponent::ColliderComponent(int minX, int minY, int width, int height)
{
    _isCollided = false;
    _isHaveFootSensor = false;
    _collisionCount = 0;

    setupCollider(minX, minY, width, height);
}

ColliderComponent::~ColliderComponent(void)
{
}

void ColliderComponent::setupCollider(int minX, int minY, int width, int height)
{
    _min.x = minX;
    _min.y = minY;

    _max.x = _min.x + width;
    _max.y = _min.y + height;

    _center.x = _min.x + (width / 2);
    _center.y = _min.y + (height / 2);

    _size.x = width;
    _size.y = height;
}

void ColliderComponent::setupFootSensor(bool isHaveFootSensor)
{
    if(isHaveFootSensor == true)
    {
        _isHaveFootSensor = true;
        _footSensor.reset(new ColliderComponent);
        _footSensor->setupCollider(_min.x, _min.y + _size.y, _size.x, 1);
    }
    else
        _isHaveFootSensor = false;
}

Vector2i& ColliderComponent::getMin()
{
    return _min;
}

Vector2i& ColliderComponent::getMax()
{
    return _max;
}

Vector2i& ColliderComponent::getCenter()
{
    return _center;
}

Vector2i& ColliderComponent::getSize()
{
    return _size;
}

void ColliderComponent::setIsCollided(bool isCollided)
{
    _isCollided = isCollided; 
}

unsigned& ColliderComponent::getCollisionCount()
{
    return _collisionCount;
}

bool ColliderComponent::getIsCollided()
{
    return _isCollided;
}

bool ColliderComponent::isHaveFootSensor()
{
    return _isHaveFootSensor;
}

shared_ptr<ColliderComponent> ColliderComponent::getFootSensor()
{
    return _footSensor;
}

bool ColliderComponent::checkCollision(shared_ptr<ColliderComponent> other)
{
    if(_isHaveFootSensor)
    {
        if(_collidedWithFootSensor != nullptr)
            if(_footSensor->checkCollision(_collidedWithFootSensor) == false)
                _footSensor->setIsCollided(false);

        if(_footSensor->checkCollision(other))
        {
            if(_collidedWithFootSensor != other)
                _collidedWithFootSensor = other;
            
            _footSensor->setIsCollided(true);
        }
    }

    Vector2i dist = other->getCenter() - _center;

    if(abs(dist.x) > (other->getSize().x / 2) + (_size.x / 2) || abs(dist.y) > (other->getSize().y / 2) + (_size.y/ 2))
        return false;

    return true;
}

void ColliderComponent::update(float deltaTime)
{
    setupCollider(_owner->getTranformComponent()._position.x, _owner->getTranformComponent()._position.y, _size.x, _size.y);

    if(_isHaveFootSensor)
        _footSensor->setupCollider(_owner->getTranformComponent()._position.x, _owner->getTranformComponent()._position.y + _size.y, _size.x, 1);
}
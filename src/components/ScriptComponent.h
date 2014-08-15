#pragma once

#include "IComponent.h"
#include "ScriptSystem.h"

class ScriptComponent : public IComponent
{
public:
    virtual void update(float deltaTime);

public:
    void addScript(const char* script, GameObject* gameObject);
    void startScriptsGameObject();
    void updateScriptsGameObject();
    void addOwnerGameObject(char* script, GameObject* gameObject);
};
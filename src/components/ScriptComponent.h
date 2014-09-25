#ifndef _SCRIPTCOMPONENT_H_
#define _SCRIPTCOMPONENT_H_

#include "IComponent.h"
#include "ScriptSystem.h"

class ScriptComponent : public IComponent
{
public:
    virtual void update(float deltaTime);

public:
    void addScript(const char* script, GameObject* gameObject);
    void startScriptsGameObject();
    void updateScriptsGameObject(float deltaTime);
    void addOwner(char* script, GameObject* gameObject);
    /*void addOwner(char* script, IComponent* component, string nameInGameObjectScriptTable);*/ // For component scripts
};

#endif
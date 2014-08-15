#ifndef _ENUMS_H_
#define _ENUMS_H_

class Enums
{
    public:

    enum ComponentIds
    {
        COMPONENT_TRANSFORM = 0,
        COMPONENT_MOVEMENT,
        COMPONENT_PLATFORMER_PHYSICS,
        COMPONENT_PLATFORMER_CONTROLLER,
        COMPONENT_ANIMATION,
        COMPONENT_SPRITE,
        COMPONENT_SCRIPT
    };
    
    enum GameObjectTypes
    {
        GAMEOBJECT_PLAYER = 0,
        GAMEOBJECT_ENEMY
    };
    
    enum Key
    {
    	KEY_PRESSED_UP = 0, // 0
    	KEY_PRESSED_DOWN,   // 1
    	KEY_PRESSED_LEFT,   // 2
    	KEY_PRESSED_RIGHT,  // 3
        KEY_PRESSED_SPACE,  // 4
    	KEY_RELEASED_LEFT,  // 5
        KEY_RELEASED_RIGHT, // 6
        KEY_RELEASED_UP,    // 7
        KEY_RELEASED_DOWN,  // 8
        KEY_RELEASED_SPACE, // 9
        KEY_NONE            // 10
    };
    
    enum Direction
    {
        DIRECTION_LEFT = 0,
        DIRECTION_RIGHT,
        DIRECTION_UP,
        DIRECTION_NONE
    };

    enum Textures
    {
        TEXTURE_PLAYER = 0,
        TEXTURE_TEST
    };
    
    enum Animations
    {
        ANIMATION_STAND_LEFT = 0,
        ANIMATION_STAND_RIGHT,
        ANIMATION_WALK_LEFT,
        ANIMATION_WALK_RIGHT,
        ANIMATION_JUMP_LEFT,
        ANIMATION_JUMP_RIGHT
    };
};
#endif


#ifndef _COMPONENTHANDLE_H_
#define _COMPONENTHANDLE_H_

struct ComponentHandle
{
    unsigned arrayIndex; // Index of component in global array of components
    unsigned type; // TYpe of Component (e.g. COMPONENT_TRANSFORM, COMPONENT_TEXTURE)
};

#endif
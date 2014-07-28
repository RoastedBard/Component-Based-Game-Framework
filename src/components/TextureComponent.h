#ifndef _TEXTURECOMPONENT_H_
#define _TEXTURECOMPONENT_H_

#include "icomponent.h"
#include <string>
#include <vector>

using namespace std;

struct TextureData
{
    unsigned _id;
    string   _filePath;
};

class TextureComponent :
    public IComponent
{
public:
    TextureComponent(void);
    ~TextureComponent(void);

public:
    vector<TextureData> getTextures() const;
    void addTexture(unsigned id, string filePath);

public:
    vector<TextureData> _textures;
};

#endif
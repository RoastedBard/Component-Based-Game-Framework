#include "TextureComponent.h"
#include "TextureManager.h"

TextureComponent::TextureComponent(void)
{
}


TextureComponent::~TextureComponent(void)
{
}

vector<TextureData> TextureComponent::getTextures() const
{
    return _textures;
}

void TextureComponent::addTexture(unsigned id, string filePath)
{
    TextureData texData;
    texData._id = id;
    texData._filePath = filePath;

    _textures.push_back(texData);
}
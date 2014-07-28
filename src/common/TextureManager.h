#ifndef _TEXTUREMANAGER_H_
#define _TEXTUREMANAGER_H_

#include <SDL.h>
#include <string>
#include <map>
#include <memory>
#include "Animation.h"

class TextureManager
{
public:
    ~TextureManager(void);

public:
    static std::shared_ptr<TextureManager> instance();

public:
    bool loadTexture(std::string filename, int id, SDL_Renderer *renderer);
    void drawTexture(int id, int x, int y, int width, int height, SDL_Renderer *renderer, SDL_RendererFlip flip = SDL_FLIP_NONE);
    void drawFrame(int id, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer *renderer, bool horizontal, SDL_RendererFlip flip = SDL_FLIP_NONE);
    void drawFrame(Animation *animation, int animationId, int screenX, int screenY, SDL_Renderer *renderer);
    std::map<int, SDL_Texture*> getTextureMap();

private:
    TextureManager(void);

private:
    std::map<int, SDL_Texture*> _textureMap; 

private:
    static std::shared_ptr<TextureManager> _instance;
};

typedef TextureManager TheTextureManager;
  
#endif
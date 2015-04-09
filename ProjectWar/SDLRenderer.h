//
//  SDLRenderer.h
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 10/3/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#ifndef __ProjectWar__SDLRenderer__
#define __ProjectWar__SDLRenderer__

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <SDL2_image/SDL_image.h>
#include "Renderer.h"
#include "SDLTexture.h"

class SDLRenderer : public Renderer
{
public:
    SDLRenderer();
    virtual ~SDLRenderer();
    void init();
    Texture* loadTexture(std::string resource);
    Texture* loadShape(Shape shape, Color color, int width, int height);
    Texture* loadText(std::string text, Color color);
    Texture* loadSprite(std::string resource, int width, int height);
    void drawTexture(Texture* texture);
    void drawTexture(Texture* texture, int width, int height);
    void renderClear();
    void renderPresent();
private:
    void drawTexture(Texture* texture, SDL_Rect destRect);
    SDL_Window* sdlWindow;
    SDL_Renderer* sdlRenderer;
    TTF_Font *sdlFont;
};

#endif /* defined(__ProjectWar__SDLRenderer__) */

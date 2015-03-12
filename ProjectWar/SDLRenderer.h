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
#include "Renderer.h"
#include "SDLTexture.h"

class SDLRenderer : public Renderer
{
public:
    SDLRenderer();
    virtual ~SDLRenderer();
    void init();
    Texture* loadTexture(std::string resource);
    void drawTexture(Texture* texture);
    void renderClear();
    void renderPresent();
private:
    SDL_Window* sdlWindow;
    SDL_Renderer* sdlRenderer;
};

#endif /* defined(__ProjectWar__SDLRenderer__) */

//
//  SDLTexture.h
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 10/3/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#ifndef __ProjectWar__SDLTexture__
#define __ProjectWar__SDLTexture__

#include <stdio.h>
#include "Texture.h"
#ifdef __APPLE__
#include <SDL2/SDL.h>
#else
#include <SDL.h>
#endif

class SDLTexture : public Texture
{
public:
    SDLTexture();
    virtual ~SDLTexture();
    void* getTexture();
    void setTexture(void* texture);
private:
    SDL_Texture* texture;
};

#endif /* defined(__ProjectWar__SDLTexture__) */

//
//  SDLTexture.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 10/3/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#include "SDLTexture.h"

SDLTexture::SDLTexture() : Texture()
{
    texture = nullptr;
}

SDLTexture::~SDLTexture()
{

}

void* SDLTexture::getTexture()
{
    return texture;
}

void SDLTexture::setTexture(void* texture)
{
    this->texture = (SDL_Texture*)texture;
}

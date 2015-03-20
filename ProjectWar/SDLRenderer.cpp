//
//  SDLRenderer.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 10/3/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#include "SDLRenderer.h"

SDLRenderer::SDLRenderer()
{
    
}

SDLRenderer::~SDLRenderer()
{
    
}

//TODO Change ir to return a boolean or a exception if something fails
void SDLRenderer::init()
{
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cout << "ERROR SDL_Init" << std::endl;
    }
    
    // create a window
    sdlWindow = SDL_CreateWindow(   "SDL 2 window",             // window title
                                 SDL_WINDOWPOS_CENTERED,     // x position, centered
                                 SDL_WINDOWPOS_CENTERED,     // y position, centered
                                 640,                        // width, in pixels
                                 480,                        // height, in pixels
                                 SDL_WINDOW_OPENGL           // flags
                                 );
    sdlRenderer = SDL_CreateRenderer(sdlWindow, -1, SDL_RENDERER_ACCELERATED);
    
    if(sdlRenderer != 0) // renderer init success
    {
        std::cout << "renderer creation success\n";
        SDL_SetRenderDrawColor(sdlRenderer, 0,0,0,255);
    }
    else
    {
        std::cout << "renderer init fail\n";
    }
    
}

//TODO Refactor loadTexture and loadSprite methods
Texture* SDLRenderer::loadTexture(std::string resource)
{
    Texture *texture = new SDLTexture;
    SDL_Rect sourceRectangle;

    SDL_Surface* pTempSurface = SDL_LoadBMP(resource.c_str());
    if(pTempSurface == 0){
        std::cout << "surface creation failed: resource: " << resource <<"\n";
    }
    
    SDL_Texture* m_pTexture = SDL_CreateTextureFromSurface(sdlRenderer,
                                                           pTempSurface);
    if(m_pTexture == 0){
        std::cout << "texture creation failed \n";
    }
    texture->setTexture(m_pTexture);
    SDL_FreeSurface(pTempSurface);
    
    SDL_QueryTexture(m_pTexture, NULL, NULL,
                     &sourceRectangle.w, &sourceRectangle.h);
    texture->setWidth(sourceRectangle.w);
    texture->setHeight(sourceRectangle.h);
    
    return texture;
}

Texture* SDLRenderer::loadSprite(std::string resource, int width, int height)
{
    Texture* texture = this->loadTexture(resource);
    texture->setFrameWidth(width);
    texture->setFrameHeight(height);
    return texture;
}

Texture* SDLRenderer::loadShape(Shape shape, Color color,int width, int height)
{
    Texture *texture = new SDLTexture;
    SDL_Surface* pTempSurface = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);
    
    /* Filling less than the surface defined just for the map appearance, change it! */
    SDL_Rect destRect;
    destRect.x = 1;
    destRect.y = 1;
    destRect.w = width - 2;
    destRect.h = height - 2;
    SDL_FillRect(pTempSurface, &destRect, SDL_MapRGB(pTempSurface->format, color.r, color.g, color.b));
    if(pTempSurface == 0){
        std::cout << "surface creation failed\n";
    }
    
    SDL_Texture* m_pTexture = SDL_CreateTextureFromSurface(sdlRenderer,
                                                           pTempSurface);
    if(m_pTexture == 0){
        std::cout << "texture creation failed \n";
    }
    texture->setTexture(m_pTexture);
    SDL_FreeSurface(pTempSurface);
    
    texture->setWidth(width);
    texture->setHeight(height);
    
    return texture;
}

//TODO Refactor drawtexture methods 
void SDLRenderer::drawTexture(Texture* texture)
{
    SDL_Rect srcRect;
    SDL_Rect destRect;
    
    srcRect.x = texture->getSourceRect().x;
    srcRect.y = texture->getSourceRect().y;
    destRect.x = texture->getPosition().x;
    destRect.y = texture->getPosition().y;
    //Check if the texture has some frameWidth or height defined in order tha animate a sprite
    //TODO change it!!
    if(texture->getFrameWidth() != 0 || texture->getFrameHeight() != 0){
        srcRect.w = destRect.w = texture->getFrameWidth();
        srcRect.h = destRect.h = texture->getFrameHeight();
    }else{
        srcRect.w = destRect.w = texture->getWidth();
        srcRect.h = destRect.h = texture->getHeight();
    }
    
    SDL_Texture* sdlTexture = (SDL_Texture*)texture->getTexture();
    SDL_RenderCopy(sdlRenderer,sdlTexture, &srcRect, &destRect);
}

void SDLRenderer::drawTexture(Texture* texture, int width, int height)
{
    SDL_Rect srcRect;
    SDL_Rect destRect;
    
    srcRect.x = texture->getSourceRect().x;
    srcRect.y = texture->getSourceRect().y;
    destRect.x = texture->getPosition().x;
    destRect.y = texture->getPosition().y;
    //Check if the texture has some frameWidth or height defined in order tha animate a sprite
    //TODO change it!!
    if(texture->getFrameWidth() != 0 || texture->getFrameHeight() != 0){
        srcRect.w = texture->getFrameWidth();
        destRect.w = width;
        srcRect.h = texture->getFrameHeight();
        destRect.h = height;
    }else{
        srcRect.w = texture->getWidth();
        destRect.w = width;
        srcRect.h = texture->getHeight();
        destRect.h = height;
    }
    
    SDL_Texture* sdlTexture = (SDL_Texture*)texture->getTexture();
    SDL_RenderCopy(sdlRenderer,sdlTexture, &srcRect, &destRect);
}

void SDLRenderer::renderPresent()
{
    SDL_RenderPresent(sdlRenderer);
}

void SDLRenderer::renderClear()
{
    SDL_RenderClear(sdlRenderer);
}






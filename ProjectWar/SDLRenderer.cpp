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

Texture* SDLRenderer::loadTexture(std::string resource)
{
    Texture *texture = new SDLTexture;
    SDL_Rect sourceRectangle; // the first rectangle
    //SDL_Surface* pTempSurface = SDL_CreateRGBSurface(0, 100, 100, 32, 0, 0, 0, 0);
    
    /* Filling the surface with red color. */
    //SDL_FillRect(pTempSurface, NULL, SDL_MapRGB(pTempSurface->format, 255, 0, 0));
    SDL_Surface* pTempSurface = SDL_LoadBMP("rider.bmp");
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
    
    SDL_QueryTexture(m_pTexture, NULL, NULL,
                     &sourceRectangle.w, &sourceRectangle.h);
    texture->setWidth(sourceRectangle.w);
    texture->setHeight(sourceRectangle.h);
    
    return texture;
}

void SDLRenderer::drawTexture(Texture* texture)
{
    SDL_Rect srcRect;
    SDL_Rect destRect;
    
    srcRect.x = 0;
    srcRect.y = 0;
    destRect.x = texture->getPosition().x;
    destRect.y = texture->getPosition().y;
    srcRect.w = destRect.w = texture->getWidth();
    srcRect.h = destRect.h = texture->getHeight();
    
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






//
//  SDLRenderer.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 10/3/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#include "SDLRenderer.h"

SDLRenderer::SDLRenderer() : sdlWindow(nullptr), sdlRenderer(nullptr), sdlFont(nullptr)
{
    camera = new Camera();
}

SDLRenderer::~SDLRenderer()
{
    
}

void SDLRenderer::registerCamera(Camera *camera)
{
    this->camera = camera;
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
    
    //Initialize SDL_ttf
    if( TTF_Init() == -1 )
    {
        printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
    }
    
    //Open the font
    sdlFont = TTF_OpenFont( "/Library/Fonts/AppleGothic.ttf", 10);
    if( sdlFont == nullptr )
    {
        printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
    }
}

Texture* SDLRenderer::loadTexture(std::string resource)
{
    Texture *texture = new SDLTexture;
    SDL_Rect sourceRectangle;

    SDL_Surface* pTempSurface = IMG_Load(resource.c_str());
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
    
    texture->setFrameWidth(sourceRectangle.w);
    texture->setFrameHeight(sourceRectangle.h);
    return texture;
}

//Sprites are always animated, so frame width and height must be defined
Texture* SDLRenderer::loadSprite(std::string resource, int width, int height)
{
    Texture* texture = this->loadTexture(resource);
    texture->setFrameWidth(width);
    texture->setFrameHeight(height);
    return texture;
}

Texture* SDLRenderer::loadText(std::string text, Color color)
{
    Texture* texture = new SDLTexture;
    SDL_Color sdlColor;
    sdlColor.r = color.r;
    sdlColor.g = color.g;
    sdlColor.b = color.b;
    //Render text surface
    SDL_Surface* textSurface = TTF_RenderText_Solid( sdlFont, text.c_str(), sdlColor );
    if( textSurface == NULL )
    {
        printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
    }
    else
    {
        //Create texture from surface pixels
        SDL_Texture* sdlTexture = SDL_CreateTextureFromSurface( sdlRenderer, textSurface );
        if( sdlTexture == NULL )
        {
            printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
        }
        else
        {
            //Get image dimensions
            texture->setTexture(sdlTexture);
            texture->setWidth(textSurface->w);
            texture->setHeight(textSurface->h);
            
            texture->setFrameWidth(textSurface->w);
            texture->setFrameHeight(textSurface->h);
        }
        
        //Get rid of old surface
        SDL_FreeSurface( textSurface );
    }
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
    
    texture->setFrameWidth(width);
    texture->setFrameHeight(height);
    return texture;
}

//draws the texture with his dimensions
void SDLRenderer::drawTexture(Texture* texture)
{
    SDL_Rect destRect;
    //If it's animated with the defined frame dimensions
    destRect.w = texture->getFrameWidth();
    destRect.h = texture->getFrameHeight();
    drawTexture(texture, destRect);
}

//method to draw resized texture, new dimensions passed as parameters
void SDLRenderer::drawTexture(Texture* texture, int width, int height)
{
    SDL_Rect destRect;
    
    destRect.w = width;
    destRect.h = height;
    drawTexture(texture, destRect);
}

void SDLRenderer::drawTexture(Texture* texture, SDL_Rect destRect)
{
    SDL_Rect srcRect;
    
    srcRect.x = texture->getFramePosition().x;
    srcRect.y = texture->getFramePosition().y;
    //TODO not working when forcing ai to render his process(black screen)
    if (texture->hud) {
        destRect.x = texture->getPosition().x;
        destRect.y = texture->getPosition().y;
    }else{
        //camera offset
        destRect.x = texture->getPosition().x - camera->position.x;
        destRect.y = texture->getPosition().y - camera->position.y;
    }
    
    srcRect.w = texture->getFrameWidth();
    srcRect.h = texture->getFrameHeight();
    
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






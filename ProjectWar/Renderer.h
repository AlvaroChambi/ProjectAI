//
//  Renderer.h
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 10/3/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#ifndef __ProjectWar__Renderer__
#define __ProjectWar__Renderer__

#include <stdio.h>
#include <iostream>
#include "Texture.h"
#include "Color.h"

enum Shape
{
    RECTANGLE,
};

class Renderer
{
public:
    virtual void init() = 0;
    virtual Texture* loadTexture(std::string resource) = 0;
    virtual Texture* loadShape(Shape shape, Color color ,int width, int height) = 0;
    virtual Texture* loadText(std::string text, Color color) = 0;
    //loadSprite returns a texture prepared for handling animations
    virtual Texture* loadSprite(std::string resource, int width, int height) = 0;
    //Draws the texture with their orginal width and height
    virtual void drawTexture(Texture* texture) = 0;
    //Draws the texture with a new width and heigth
    virtual void drawTexture(Texture* texture, int width, int height) = 0;
    
    virtual void renderClear() = 0;
    virtual void renderPresent() = 0;
};

#endif /* defined(__ProjectWar__Renderer__) */

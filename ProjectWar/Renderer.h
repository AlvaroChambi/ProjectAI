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

class Renderer
{
public:
    virtual void init() = 0;
    virtual Texture* loadTexture(std::string resource) = 0;
    virtual void drawTexture(Texture* texture) = 0;
    virtual void renderClear() = 0;
    virtual void renderPresent() = 0;
};

#endif /* defined(__ProjectWar__Renderer__) */

//
//  Text.h
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 2/4/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#ifndef __ProjectWar__Text__
#define __ProjectWar__Text__

#include <stdio.h>
#include <iostream>
#include "Texture.h"
#include "UIComponent.h"

class Text : public UIComponent
{
public:
    Text();
    Text(int id);
    virtual ~Text();
    void render(Renderer* renderer);
    UIComponent* matchEvent(Point position);
    void setTextResource(std::string text);
    
    Texture* texture;
    std::string resource;
    //Flag to know if the text resource has been changed
    bool changed;
};

#endif /* defined(__ProjectWar__Text__) */

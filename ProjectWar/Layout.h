//
//  Layout.h
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 24/3/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#ifndef __ProjectWar__Layout__
#define __ProjectWar__Layout__

#include <stdio.h>

#include "UIComponent.h"

class Layout : public UIComponent
{
public:
    Layout();
    virtual ~Layout();
    void render(Renderer* renderer);
    void addComponent(UIComponent* component);
    void setBackground(Texture* background);
    UIComponent* matchEvent(Point position);
private:
    //TODO Change it for a linked list
    UIComponent* components[20];
    Texture* background;
    int numComponents;
};

#endif /* defined(__ProjectWar__Layout__) */

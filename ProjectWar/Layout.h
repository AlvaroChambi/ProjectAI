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
#include "List.h"
#include "Params.h"


#include "UIComponent.h"

class Layout : public UIComponent
{
public:
    Layout();
    virtual ~Layout();
    void render(Renderer* renderer);
    void addComponent(UIComponent* component);
    void setBackground(Texture* background);
    void updatePosition();
    UIComponent* matchEvent(Point position);
private:
    List <UIComponent*> components;
    Texture* background;
};

#endif /* defined(__ProjectWar__Layout__) */

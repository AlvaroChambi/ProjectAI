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
#include <list>
#include "Params.h"


#include "UIComponent.h"

class Layout : public UIComponent
{
public:
    Layout();
    Layout(int id);
    virtual ~Layout();
    virtual void addComponent(UIComponent* component);
    void render(Renderer* renderer);
    void setBackground(Texture* background);
    void setBackground(Color color);
    UIComponent* matchEvent(Point position);
    void cleanComponents();
protected:
    std::list<UIComponent*> components;
private:
    Texture* background;
};

#endif /* defined(__ProjectWar__Layout__) */

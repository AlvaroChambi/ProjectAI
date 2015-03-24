//
//  UIComponent.h
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 24/3/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#ifndef ProjectWar_UIComponent_h
#define ProjectWar_UIComponent_h

#include "Renderer.h"
#include "Params.h"

class UIComponent
{
public:
    UIComponent();
    virtual ~UIComponent();
    virtual void render(Renderer* renderer) = 0;
    virtual UIComponent* matchEvent(Point position) = 0;
    
    void setParams(Params params);
    
    void setPosition(int x, int y);
    Point getPosition();
    
    void setWidth(int width);
    int getWidth();
    
    void setHeight(int height);
    int getHeight();
    
    void setParent(UIComponent* component);
    UIComponent* getParent();
protected:
    void updateValues();
private:
    void updatePosition();
    void updateDimensions();
    
    UIComponent* parent;
    Params params;
    Point position;
    int width;
    int height;
};

#endif

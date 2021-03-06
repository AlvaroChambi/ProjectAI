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
    UIComponent(int id);
    virtual ~UIComponent();
    virtual void render(Renderer* renderer) = 0;
    virtual UIComponent* matchEvent(Point position) = 0;
    
    void setParams(Params params);
    Params getParams();
    
    void setID(int id);
    int getID();
    
    void setPosition(int x, int y);
    void setPosition(Point position);
    Point getPosition() const;
    
    void setWidth(int width);
    int getWidth();
    
    void setHeight(int height);
    int getHeight();
    
    void setParent(UIComponent* component);
    UIComponent* getParent();

    void center(Point parentPosition, int parentWidth, int parentHeight);
    void up(Point parentPosition, int parentWidth, int parentHeight);
    void down(Point parentPosition, int parentWidth, int parentHeight);
    void centerDown(Point parentPosition, int parentWidth, int parentHeight);
    
    virtual void updateValues();
    virtual void updatePosition();
    virtual void updateDimensions();
    
    int id;
    UIComponent* parent;
    Params params;
    Point position;
    int width;
    int height;
};

#endif

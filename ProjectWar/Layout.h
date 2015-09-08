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
#include <vector>
#include "Params.h"


#include "UIComponent.h"

class Layout : public UIComponent
{
public:
    Layout();
    virtual ~Layout();
    virtual void addComponent(UIComponent* component);
    void render(Renderer* renderer);
    void setBackground(Texture* background);
    void setBackground(Color color);
    UIComponent* matchEvent(Point position);
    void cleanComponents();
    
    void resize(float widthRatio, float heightRatio);
    virtual void onMeasureCompleted();
    virtual void onMeasureChanged();
    virtual void measureDisposition();
    void populateLayout(std::vector<Point> dispositionPoints);
    void assignFrames(std::vector<Point> dispositionPoints);
    virtual void assignFrames(std::vector<Point>dispositionPoints, std::vector<UIComponent*> components);
    
    std::vector<Point> layoutDisposition();
    std::list<UIComponent*> components;
private:
    //TODO remove
    Texture* background;
    Color* backgroundColor;
};

#endif /* defined(__ProjectWar__Layout__) */

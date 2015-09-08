//
//  ProjectedLayout.h
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 3/9/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#ifndef __ProjectWar__ProjectedLayout__
#define __ProjectWar__ProjectedLayout__

#include <stdio.h>
#include "Layout.h"

class ProjectedLayout : public Layout
{
public:
    ProjectedLayout();
    virtual ~ProjectedLayout();
    
    void render(Renderer* renderer);
    void measureDisposition();
    
    std::vector<Point> projectedLayoutsDisposition();
    std::vector<UIComponent*> layoutFrames;
    void assignFrames(std::vector<Point>dispositionPoints, std::vector<UIComponent*> components);
    int maxDepthLevel;
    int actualDepthLevel;
    
    void addComponent(UIComponent* component);
    void moveToUpperLevel();
    void moveToLowerLevel();
    void project();
};

#endif /* defined(__ProjectWar__ProjectedLayout__) */

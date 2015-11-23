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
#include "HorizontalLayout.h"
#include "Node.h"
#include "MenuContainer.h"
#include "ProjectedLayoutFrame.h"

class ProjectedLayout : public Layout, OnItemClickedListener
{
public:
    typedef std::pair<Point, float> FrameBundle;
    
    ProjectedLayout();
    virtual ~ProjectedLayout();
    
    void render(Renderer* renderer);
    void measureDisposition();
    
    bool handleEvent(const Event event);
    
    void onItemClicked(UIComponent* component);
    
    void onContentMeasureCompleted();
    
    std::vector<Point> projectedLayoutsDisposition();
    std::vector<HorizontalLayout*> layoutFrames;
    void assignFrames(std::vector<Point>dispositionPoints, std::vector<UIComponent*> components);
    void populateLayout(std::vector<Point>dispositionPoints);
    int maxDepthLevel;
    int actualDepthLevel;
    MenuContainer* menuContainer;
    
    void addComponent(UIComponent* component);
    void moveToUpperLevel();
    void moveToLowerLevel();
    void project(UIComponent* component);
    
    void moveFrameDown(ProjectedLayoutFrame* frame);
    void moveFrameUp(ProjectedLayoutFrame* frame);
    
    FrameBundle getFrameBundle(int frameLevel);
    
    std::vector<FrameBundle> fixedValues;
    
    Node<UIComponent*>* root;
    
    std::vector<ProjectedLayoutFrame*> frames;
};

#endif /* defined(__ProjectWar__ProjectedLayout__) */

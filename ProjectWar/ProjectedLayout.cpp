//
//  ProjectedLayout.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 3/9/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#include "ProjectedLayout.h"


ProjectedLayout::ProjectedLayout() : Layout(), maxDepthLevel(2), actualDepthLevel(0)
{

}

ProjectedLayout::~ProjectedLayout()
{

}

void ProjectedLayout::addComponent(UIComponent *component)
{

}

void ProjectedLayout::moveToLowerLevel()
{

}

void ProjectedLayout::moveToUpperLevel()
{

}

void ProjectedLayout::measureDisposition()
{
    std::vector<Point> dispositionPoints = projectedLayoutsDisposition();
    //TODO all the projected layouts has the dimension of the depth0 layout
    assignFrames(dispositionPoints);
    populateLayout(dispositionPoints);
}

std::vector<Point> ProjectedLayout::projectedLayoutsDisposition()
{
    std::vector<Point> dispositionPoints;
    
    int projectionHeight = height/2;
    
    Point start;
    Point end;
    start.x = position.x;
    start.y = position.y + projectionHeight/2;
    end.x = start.x + width * 1;
    end.y = start.y + projectionHeight;
    dispositionPoints.push_back(start);
    dispositionPoints.push_back(end);
    
    start.x = position.x + width/8;
    start.y = position.y + (projectionHeight/4) + (projectionHeight/8);
    end.x = start.x + width * 0.75;
    end.y = start.y + projectionHeight * 0.75;
    dispositionPoints.push_back(start);
    dispositionPoints.push_back(end);
    
    start.x = position.x + width/4;
    start.y = position.y + projectionHeight/4;
    end.x = start.x + width * 0.5;
    end.y = start.y + projectionHeight * 0.5;
    dispositionPoints.push_back(start);
    dispositionPoints.push_back(end);
    
    return dispositionPoints;
}
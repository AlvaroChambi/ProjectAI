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
    for (int i = 0; i <= maxDepthLevel; i++) {
        layoutFrames.push_back(new Layout);
    }
}

ProjectedLayout::~ProjectedLayout()
{

}

void ProjectedLayout::render(Renderer *renderer)
{
    //UIComponent::render(renderer);
    renderer->renderDrawShape(RECTANGLE_OUTLINE, position, Color(255, 0, 0), width, height);
    
    components.reverse();
    for (UIComponent* component : components) {
        component->render(renderer);
    }
    components.reverse();
}

void ProjectedLayout::addComponent(UIComponent *component)
{
    Layout::addComponent(component);
    /*
    components.push_back(component);
    component->setParent(this);
    component->setHUD(hud);*/
}

void ProjectedLayout::moveToLowerLevel()
{

}

void ProjectedLayout::moveToUpperLevel()
{

}

void ProjectedLayout::project()
{
     std::vector<Point> dispositionPoints = projectedLayoutsDisposition();
     std::vector<UIComponent*> componentsVector(components.begin(), components.end());
     UIComponent* component0 = componentsVector.at(0);
     UIComponent* component1 = componentsVector.at(1);
     UIComponent* component2 = componentsVector.at(2);
     //For each depth level position and dimensions changed
     component0->position = dispositionPoints.at(0);
     component0->resize(1, 1);
     
     component1->position = dispositionPoints.at(2);
     component1->resize(0.75, 0.75);
     
     component2->position = dispositionPoints.at(4);
     component2->resize(0.5, 0.5);
}

void ProjectedLayout::measureDisposition()
{
    std::vector<Point> dispositionPoints = projectedLayoutsDisposition();
    Layout::assignFrames(dispositionPoints);
    for (UIComponent* component : components) {
        component->setWidth(component->frame.width);
        component->setHeight(component->frame.height);
    }
    populateLayout(dispositionPoints);
}

void ProjectedLayout::assignFrames(std::vector<Point> dispositionPoints, std::vector<UIComponent *> components)
{
    Point start = dispositionPoints.at(0);
    Point end = dispositionPoints.at(1);
    for (UIComponent* component : components) {
        component->frame.position = start;
        component->frame.width = end.x - start.x;
        component->frame.height = end.y - start.y;
    }
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
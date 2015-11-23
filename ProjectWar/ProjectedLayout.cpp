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
    this->listener = this;
    for (int i = 0; i <= maxDepthLevel; i++) {
        HorizontalLayout* layout = new HorizontalLayout;
        layout->listener = this;
        layout->params.disposition = WEIGHT_DISPOSITION;
        layout->hud = true;
        layoutFrames.push_back(layout);
    }
}

ProjectedLayout::~ProjectedLayout()
{

}

void ProjectedLayout::render(Renderer *renderer)
{
    //UIComponent::render(renderer);
    for (Layout* layout : layoutFrames) {
        layout->render(renderer);
    }
    renderer->renderDrawShape(RECTANGLE_OUTLINE, position, Color(255, 0, 0), width, height);
    
    components.reverse();
    for (UIComponent* component : components) {
        component->render(renderer);
    }
    components.reverse();
}

bool ProjectedLayout::handleEvent(const Event event)
{
    bool result = false;
    
    //just handling events of the depth 0 level layout
    layoutFrames.at(0)->handleEvent(event);
    
    return result;
}

void ProjectedLayout::onItemClicked(UIComponent *component)
{
    //get graph node
    std::cout << "component clicked: " << component->position << std::endl;
    std::vector<UIComponent*> childs = menuContainer->getChilds(component);
    if (!childs.empty()) {
        actualDepthLevel++;
        project(component);
    }
}

//
    //Given a (UIComponent)graph node update layout view
//

void ProjectedLayout::onContentMeasureCompleted()
{
    std::cout << "content measure completed" << std::endl;
    project(nullptr);
}

void ProjectedLayout::addComponent(UIComponent *component)
{
    Layout::addComponent(component);
}

void ProjectedLayout::moveToLowerLevel()
{
    for (ProjectedLayoutFrame* frame : frames) {
        moveFrameDown(frame);
    }
}

void ProjectedLayout::moveToUpperLevel()
{
    for (ProjectedLayoutFrame* frame : frames) {
        moveFrameUp(frame);
    }
}

void ProjectedLayout::moveFrameDown(ProjectedLayoutFrame* frame)
{
    int frameLevel = frame->frameLevel - 1;
    if (frameLevel < 0) {
        frameLevel = 3;
    }
    frame->moveFrame(getFrameBundle(frameLevel));
    frame->frameLevel = frameLevel;
}

void ProjectedLayout::moveFrameUp(ProjectedLayoutFrame* frame)
{
    int frameLevel = frame->frameLevel + 1;
    if (frameLevel > 3) {
        frameLevel = 3;
    }
    frame->moveFrame(getFrameBundle(frameLevel));
    frame->frameLevel = frameLevel;
}

ProjectedLayout::FrameBundle ProjectedLayout::getFrameBundle(int frameLevel)
{
    ProjectedLayout::FrameBundle bundle = fixedValues[frameLevel];
    return bundle;
}

void ProjectedLayout::project(UIComponent* component)
{
    std::vector<Point> dispositionPoints = projectedLayoutsDisposition();
    Layout* component0 = layoutFrames.at(0);
    Layout* component1 = layoutFrames.at(1);
    Layout* component2 = layoutFrames.at(2);
    
    std::vector<UIComponent*> childs;
    
    if (actualDepthLevel == 0) {
        childs = menuContainer->getRootChilds();
        for (UIComponent* component : childs) {
            component0->addComponent(component);
        }
    }else if(actualDepthLevel == 1){
        childs = menuContainer->getChilds(component);
        for (UIComponent* component : childs) {
            component0->addComponent(component);
        }
        for (UIComponent* component : menuContainer->getRootChilds()) {
            component1->addComponent(component);
        }
        // for nodes of upper level
            //populate component1
    }else if(actualDepthLevel == 2){
        childs = menuContainer->getChilds(component);
        childs = menuContainer->getChilds(component);
        for (UIComponent* component : childs) {
            component0->addComponent(component);
        }
        // for nodes of upper level
        //populate component1
        
        // for nodes of upper upper level
        //populate component2
    }
    Layout::assignFrames(dispositionPoints);
    for (UIComponent* component : layoutFrames) {
        component->position = component->frame.position;
        component->setWidth(component->frame.width);
        component->setHeight(component->frame.height);
    }
    //For each depth level position and dimensions are changed
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
    for (UIComponent* component : layoutFrames) {
        component->position = component->frame.position;
        component->setWidth(component->frame.width);
        component->setHeight(component->frame.height);
    }
    populateLayout(dispositionPoints);
}

void ProjectedLayout::populateLayout(std::vector<Point> dispositionPoints)
{
    Layout::populateLayout(dispositionPoints);
}

void ProjectedLayout::assignFrames(std::vector<Point> dispositionPoints, std::vector<UIComponent *> components)
{
    Point start = dispositionPoints.at(0);
    Point end = dispositionPoints.at(1);
    for (UIComponent* component : layoutFrames) {
        component->frame.position = start;
        component->frame.width = end.x - start.x;
        component->frame.height = end.y - start.y;
        
        menuFrame = component->frame;
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
    
    for (int i = 0; i < 6; i = i + 2) {
        FrameBundle bundle;
        bundle.first = dispositionPoints[i];
        fixedValues.push_back(bundle);
    }
    
    fixedValues.at(0).second = 1;
    fixedValues.at(1).second = 0.75;
    fixedValues.at(2).second = 0.5;
    //fixedValues.at(3).second = 0;
    //fixedValues.at(3).first = Point(0,0);
    
    return dispositionPoints;
}
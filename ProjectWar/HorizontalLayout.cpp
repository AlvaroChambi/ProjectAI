//
//  HorizontalLayout.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 12/6/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#include "HorizontalLayout.h"

HorizontalLayout::HorizontalLayout() : Layout()
{

}

HorizontalLayout::~HorizontalLayout()
{

}

void HorizontalLayout::measureDisposition()
{
    if(components.size() > 0){
        int subParentWidth = getWidth() / components.size();
        int i = 0;
        for (UIComponent* component : components) {
            int subParentX = getPosition().x + subParentWidth * i;
            Point subParentPosition = Point(subParentX, getPosition().y);
            component->measurePosition(subParentPosition, subParentWidth, getHeight());
            i++;
        }
    }
}

std::vector<Point> HorizontalLayout::wrapDisposition()
{
    std::vector<Point> dispositionPoints;
    for (UIComponent* component :  components) {
        Point start = position;
        Point end;
        //If there are a previous end point start from there
        if (!dispositionPoints.empty()) {
            start.x = dispositionPoints.back().x;
        }
        dispositionPoints.push_back(start);
        
        end.x = start.x + component->width;
        end.y = position.y + component->height;
        
        if (end.y != position.y + height) {
            end.y = position.y + height;
        }else if(end.x > position.x + width){
            //If height limit is reached add the last point adjusted and finish
            //all the other elements will not be drawed
            end.x = position.x + width;
            dispositionPoints.push_back(end);
            return dispositionPoints;
        }
        dispositionPoints.push_back(end);
    }
    return dispositionPoints;
}

std::vector<Point> HorizontalLayout::weightDisposition()
{
    std::vector<Point> dispositionPoints;
    float weightSum = 0;
    float actualWeight = 0;
    for (UIComponent* component :  components) {
        if (component->weight < 0) {
            component->weight = 0;
        }
        weightSum = weightSum + component->weight;
    }
    
    for (UIComponent* component : components) {
        Point start = position;
        Point end;
        
        //If there are a previous end point start from there
        if (!dispositionPoints.empty()) {
            start.x = dispositionPoints.back().x;
        }
        
        dispositionPoints.push_back(start);
        if (weightSum > 0) {
            actualWeight = component->weight / weightSum;
        }
        
        end.x = start.x + width * actualWeight;
        end.y = position.y + component->height;
        if (end.y != position.y + height) {
            end.y = position.y + height;
        }
        
        dispositionPoints.push_back(end);
    }
    return dispositionPoints;
}

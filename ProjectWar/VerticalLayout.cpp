//
//  VerticalLayout.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 8/6/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#include "VerticalLayout.h"

//TODO building with and undefined id
VerticalLayout::VerticalLayout() : Layout(-1)
{
    
}

VerticalLayout::~VerticalLayout()
{

}

void VerticalLayout::measurePosition()
{
    if(components.size() > 0){
        int subParentHeight = getHeight() / components.size();
        int i = 0;
        for (UIComponent* component : components) {
            int subParentY = getPosition().y + subParentHeight * i;
            Point subParentPosition = Point(getPosition().x, subParentY);
            component->center(subParentPosition, getWidth(), subParentHeight);
            i++;
        }
    }

}
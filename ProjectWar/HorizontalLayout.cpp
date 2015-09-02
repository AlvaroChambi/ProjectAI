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

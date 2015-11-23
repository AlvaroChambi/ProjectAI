//
//  ProjectedLayoutFrame.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 16/9/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#include "ProjectedLayoutFrame.h"

ProjectedLayoutFrame::ProjectedLayoutFrame() : layout()
{
    
}

ProjectedLayoutFrame::~ProjectedLayoutFrame()
{

}

void ProjectedLayoutFrame::moveFrame(std::pair<Point, float> bundle)
{
    layout->resetSize();
    int widthRatio, heightRatio = bundle.second;
    Point position = bundle.first;
    
    layout->position = position;
    layout->UIComponent::resize(widthRatio, heightRatio);
}



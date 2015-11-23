//
//  ProjectedLayoutFrame.h
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 16/9/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#ifndef __ProjectWar__ProjectedLayoutFrame__
#define __ProjectWar__ProjectedLayoutFrame__

#include <stdio.h>
#include "HorizontalLayout.h"

class ProjectedLayoutFrame
{
public:
    ProjectedLayoutFrame();
    ~ProjectedLayoutFrame();
    
    int frameLevel;
    
    void moveFrame(std::pair<Point, float> bundle);
    
    HorizontalLayout* layout;
};

#endif /* defined(__ProjectWar__ProjectedLayoutFrame__) */

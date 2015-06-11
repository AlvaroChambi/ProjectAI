//
//  BuildingFactory.h
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 9/6/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#ifndef __ProjectWar__BuildingFactory__
#define __ProjectWar__BuildingFactory__

#include <stdio.h>
#include "Building.h"

class BuildingFactory
{
public:
    BuildingFactory();
    ~BuildingFactory();
    
    Building* createBuilding(std::string scriptFile);
};

#endif /* defined(__ProjectWar__BuildingFactory__) */

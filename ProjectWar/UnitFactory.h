//
//  UnitFactory.h
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 2/6/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#ifndef __ProjectWar__UnitFactory__
#define __ProjectWar__UnitFactory__


#include "UnitFactory.h"
#include <iostream>
#include "Unit.h"

class UnitFactory
{
public:
    UnitFactory();
    ~UnitFactory();
    
    //Create a unit from a script
    Unit* createUnit(std::string script);
    
};

#endif /* defined(__ProjectWar__UnitFactory__) */

//
//  UnitController.h
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 17/3/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#ifndef __ProjectWar__UnitController__
#define __ProjectWar__UnitController__

#include <stdio.h>
#include "Unit.h"

class UnitController
{
public:
    UnitController();
    virtual ~UnitController();
    
private:
    Unit* unit;
};

#endif /* defined(__ProjectWar__UnitController__) */

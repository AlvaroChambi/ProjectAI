
//
//  Observer.h
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 15/3/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#ifndef __ProjectWar__Observer__
#define __ProjectWar__Observer__

#include <stdio.h>

enum Update
{
    POSITION_UPDATE,
    SELECTED_UPDATE,
    ACTIVE_UPDATE,
};

class Observer
{
public:
    //TODO add something like a update type as a parameter...
    virtual void update( Update update ) = 0;
};

#endif /* defined(__ProjectWar__Observer__) */

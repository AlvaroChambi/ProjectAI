
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
    COMMANDS_UPDATE,
    HP_UPDATE,
    STATE_UPDATE,
    CAPTURE_UPDATE,
};

class Observer
{
public:
    virtual void update( Update update ) = 0;
};

#endif /* defined(__ProjectWar__Observer__) */

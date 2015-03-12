//
//  Event.h
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 12/3/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#ifndef __ProjectWar__Event__
#define __ProjectWar__Event__

#include <stdio.h>

enum EventType
{
    ON_WINDOW_CLOSED,
    ON_MOUSE_DOWN_EVENT,
    EVENT_NONE
};

class Event
{
public:
    Event();
    EventType type;
    int x;
    int y;
private:
    
};

#endif /* defined(__ProjectWar__Event__) */

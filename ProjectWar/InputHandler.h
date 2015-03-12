//
//  InputHandler.h
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 10/3/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#ifndef __ProjectWar__InputHandler__
#define __ProjectWar__InputHandler__

#include <stdio.h>
#include "Event.h"

class InputHandler
{
public:
    virtual void initInputHandler() = 0;
    virtual Event* poolEvent() = 0;
};

#endif /* defined(__ProjectWar__InputHandler__) */

//
//  Movement.h
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 22/4/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#ifndef __ProjectWar__Movement__
#define __ProjectWar__Movement__

#include <stdio.h>
#include "Command.h"
#include "List.h"

class Movement
{
public:
    Movement();
    Movement(int score);
    Movement(List<Command*>* commands, int score);
    void execute();
    void cancel();
    virtual ~Movement();

    int score;
    List<Command*>* commands;
};

#endif /* defined(__ProjectWar__Movement__) */

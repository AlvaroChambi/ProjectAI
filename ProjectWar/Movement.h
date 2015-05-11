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
#include <list>
#include "Command.h"

class Movement
{
public:
    Movement();
    //TODO maybe remove score...
    Movement(int score);
    Movement(std::list<Command*>* commands);
    Movement(std::list<Command*>* commands, int score);
    void execute();
    void cancel();
    int getScore();
    virtual ~Movement();

    int score;
    std::list<Command*>* commands;
};

#endif /* defined(__ProjectWar__Movement__) */

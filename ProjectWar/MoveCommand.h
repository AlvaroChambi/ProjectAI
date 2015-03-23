//
//  MoveCommand.h
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 21/3/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#ifndef __ProjectWar__MoveCommand__
#define __ProjectWar__MoveCommand__

#include <stdio.h>

#include "Command.h"
#include "Unit.h"

class MoveCommand : public Command
{
public:
    MoveCommand(Unit* unit);
    ~MoveCommand();
    
    void execute();
    void cancel();
private:
    Unit* unit;
};

#endif /* defined(__ProjectWar__MoveCommand__) */

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
class Map;
class MoveCommand : public Command
{
public:
    MoveCommand(Unit* unit,Map* map ,Tile destination);
    virtual ~MoveCommand();
    
    void execute();
    void cancel();
private:
    Map* map;
    Unit* unit;
    Tile savedPosition;
    Tile destination;
};

#endif /* defined(__ProjectWar__MoveCommand__) */

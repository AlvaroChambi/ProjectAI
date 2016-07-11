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
class IMap;
class MoveCommand : public Command
{
public:
    MoveCommand( MapContext& mapContext, int unitID, const Point& destination );
    virtual ~MoveCommand();
    
    bool changeContext( MapContext& mapContext );
    void execute();
    void cancel();
private:
    MapContext& mapContext;
    const int unitID;
    const Point& destination;
    
    Point savedPosition;
    bool executed;
};

#endif /* defined(__ProjectWar__MoveCommand__) */

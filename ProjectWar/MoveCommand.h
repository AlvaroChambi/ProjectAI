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
class MoveCommand : public Command {
public:
    MoveCommand( int unitID, const Point destination );
    MoveCommand( const MoveCommand& moveCommand );
    virtual ~MoveCommand();
    
    bool changeContext( MapContext& context );
    void execute( MapContext& mapContext );
    void cancel();
    Command& clone();
    
    const Point& getDestination() const;
    bool operator==( const MoveCommand& moveCommand ) const ;
    
    const int getUnitID() const;
private:
    MapContext* mapContext;
    const int unitID;
    const Point destination;
    
    Point savedPosition;
};

#endif /* defined(__ProjectWar__MoveCommand__) */

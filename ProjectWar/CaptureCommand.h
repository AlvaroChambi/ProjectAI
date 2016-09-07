//
//  CaptureCommand.h
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 11/4/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#ifndef __ProjectWar__CaptureCommand__
#define __ProjectWar__CaptureCommand__

#include <stdio.h>
#include "Command.h"
#include "Player.h"
#include "Building.h"

class CaptureCommand : public Command {
public:
    CaptureCommand( const int unitID );
    CaptureCommand( const CaptureCommand& captureCommand );
    virtual ~CaptureCommand();
    
    void execute( MapContext& context );
    void cancel();
    Command& clone();
private:
    const int unitID;
    int buildingID;
    
    MapContext* mapContext;
    
    int savedOwner;
    int savedCaptureValue;
};

#endif /* defined(__ProjectWar__CaptureCommand__) */

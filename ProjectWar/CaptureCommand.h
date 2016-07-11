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
    CaptureCommand( MapContext& mapContext, const int unitID );
    virtual ~CaptureCommand();
    
    bool changeContext( MapContext& mapContext );
    void execute();
    void cancel();
private:
    const int unitID;
    int buildingID;
    
    MapContext* mapContext;
    
    bool executed;
    
    int savedOwner;
    int savedCaptureValue;
};

#endif /* defined(__ProjectWar__CaptureCommand__) */

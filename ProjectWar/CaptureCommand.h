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

class CaptureCommand : public Command
{
public:
    CaptureCommand( Player* player, Unit* unit, Building* building );
    virtual ~CaptureCommand();
    
    bool changeContext( MapContext& mapContext );
    void execute();
    void cancel();
private:
    Player* player;
    Unit* unit;
    Building* building;
    int savedOwner;
    int savedCaptureValue;
};

#endif /* defined(__ProjectWar__CaptureCommand__) */

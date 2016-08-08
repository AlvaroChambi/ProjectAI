//
//  AttackCommand.h
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 7/4/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#ifndef __ProjectWar__AttackCommand__
#define __ProjectWar__AttackCommand__

#include <stdio.h>
#include "Command.h"
#include "Player.h"

class AttackCommand : public Command {
public:
    AttackCommand( const int unitID, const int targetID );
    
    void execute( MapContext& context );
    void cancel();
private:
    int unitID;
    int targetID;
    
    Unit* savedUnit;
    Unit* savedTarget;
    
    MapContext* mapContext;
    
    int savedUnitHP;
    int savedTargetHP;
    
    void updateHP(Unit* attacker, Unit* attacked);
};

#endif /* defined(__ProjectWar__AttackCommand__) */

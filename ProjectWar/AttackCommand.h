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

class AttackCommand : public Command
{
public:
    AttackCommand(Unit* unit, Unit* enemyUnit);
    virtual ~AttackCommand();
    void cancel();
    void execute();
private:
    Unit* unit;
    Unit* enemyUnit;
};

#endif /* defined(__ProjectWar__AttackCommand__) */

//
//  AttackCommand.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 7/4/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#include "AttackCommand.h"

AttackCommand::AttackCommand(Unit* unit, Unit* enemyUnit) : unit(unit), enemyUnit(enemyUnit)
{
    
}

AttackCommand::~AttackCommand()
{

}

void AttackCommand::execute()
{
    std::cout << "executing attack command\n";
}

void AttackCommand::cancel()
{
    std::cout << "cancelling attack command\n";
}



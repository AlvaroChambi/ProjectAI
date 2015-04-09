//
//  AttackCommand.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 7/4/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#include "AttackCommand.h"

AttackCommand::AttackCommand(Unit* unit, Unit* targetUnit) : unit(unit), targetUnit(targetUnit)
{
    this->unit = unit;
    this->targetUnit = targetUnit;
    this->savedUnitHP = unit->getHP();
    this->savedTargetHP = targetUnit->getHP();
}

AttackCommand::~AttackCommand()
{

}

void AttackCommand::execute()
{
    std::cout << "executing attack command\n";
    updateHP(unit, targetUnit);
    updateHP(targetUnit, unit);
}

void AttackCommand::cancel()
{
    std::cout << "cancelling attack command\n";
    unit->setHP(savedUnitHP);
    targetUnit->setHP(savedTargetHP);
}

void AttackCommand::updateHP(Unit* attacker,Unit* attacked)
{
    int damage = attacker->getHP() * 0.5;
    attacked->setHP(attacked->getHP() - damage);
}


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
    //std::cout << "executing attack command\n";
    updateHP(unit, targetUnit);
    if (targetUnit->getHP() < 0) {
        targetUnit->setHP(0);
    }
    updateHP(targetUnit, unit);
    if (unit->getHP() < 0) {
        unit->setHP(0);
    }
}

void AttackCommand::cancel()
{
    std::cout << "              cancelling attack command\n";
    unit->setHP(savedUnitHP);
    targetUnit->setHP(savedTargetHP);
}

void AttackCommand::updateHP(Unit* attacker,Unit* attacked)
{
    std::cout << "              executing attack command\n";
    int damage = attacker->getHP() * 0.5;
    attacked->setHP(attacked->getHP() - damage);
}


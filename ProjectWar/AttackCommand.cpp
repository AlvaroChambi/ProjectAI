//
//  AttackCommand.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 7/4/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#include "AttackCommand.h"
#include "Map.h"

AttackCommand::AttackCommand(Unit* unit, Unit* targetUnit, Map* map)
: unit(unit), targetUnit(targetUnit), map( map ) {
    this->savedUnitHP = unit->getHP();
    this->savedTargetHP = targetUnit->getHP();
}

AttackCommand::~AttackCommand() {

}

void AttackCommand::execute() {
    updateHP( unit, targetUnit );
    if (targetUnit->getHP() <= 0) {
        targetUnit->setHP(0);
        targetUnit->updateState();
        map->removeUnit( *targetUnit );
    }
    
    if( unit->getHP() <= 0 ) {
        unit->setHP(0);
        unit->updateState();
        map->removeUnit( *unit );
    }
    
    updateHP( targetUnit, unit );
    if (unit->getHP() <= 0) {
        unit->setHP(0);
        unit->updateState();
        map->removeUnit( *unit );
    }
    
    if( targetUnit->getHP() <= 0 ) {
        targetUnit->setHP(0);
        targetUnit->updateState();
        map->removeUnit( *targetUnit );
    }
}

void AttackCommand::cancel() {
    
    unit->setHP( savedUnitHP );
    targetUnit->setHP( savedTargetHP );

    map->restoreUnit( *unit );
    map->restoreUnit( *targetUnit );
    unit->updateState();
    targetUnit->updateState();
}

void AttackCommand::updateHP( Unit* attacker,Unit* attacked ) {
    int damage = attacker->getHP() * 0.5;
    attacked->setHP( attacked->getHP() - damage );
}


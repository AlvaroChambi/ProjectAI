//
//  AttackCommand.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 7/4/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#include "AttackCommand.h"
#include "Map.h"

AttackCommand::AttackCommand( MapContext& mapContext,
                              const int unitID, const int targetID )
: unitID( unitID ), targetID( targetID ), mapContext( mapContext ),
 executed( false ) {

}

bool AttackCommand::changeContext( MapContext &mapContext ) {
    if ( !executed ) {
        this->mapContext = mapContext;
    }
    return false;
}

void AttackCommand::execute() {
    Unit* unit = mapContext.getEntity( unitID );
    Unit* targetUnit = mapContext.getEntity( targetID );
    
    savedUnit = unit;
    savedTarget = targetUnit;
    
    if( targetUnit != nullptr ) {
        savedUnitHP = unit->getHP();
        savedTargetHP = targetUnit->getHP();
        
        updateHP( unit, targetUnit );
        if ( targetUnit->getHP() <= 0 ) {
            targetUnit->setHP( 0 );
            targetUnit->updateState();
            mapContext.removeUnit( *targetUnit );
        }
        
        if( unit->getHP() <= 0 ) {
            unit->setHP( 0 );
            unit->updateState();
            mapContext.removeUnit( *unit );
        }
        
        updateHP( targetUnit, unit );
        if ( unit->getHP() <= 0 ) {
            unit->setHP( 0 );
            unit->updateState();
            mapContext.removeUnit( *unit );
        }
        
        if( targetUnit->getHP() <= 0 ) {
            targetUnit->setHP( 0 );
            targetUnit->updateState();
            mapContext.removeUnit( *targetUnit );
        }
    }
    executed = true;
}

void AttackCommand::cancel() {
    if( savedTarget != nullptr ) {
        savedUnit->setHP( savedUnitHP );
        savedTarget->setHP( savedTargetHP );
        
        mapContext.restoreUnit( *savedUnit );
        mapContext.restoreUnit( *savedTarget );
        savedUnit->updateState();
        savedTarget->updateState();
    }
    executed = false;
}

void AttackCommand::updateHP( Unit* attacker, Unit* attacked ) {
    int damage = attacker->getHP() * 0.5;
    attacked->setHP( attacked->getHP() - damage );
}


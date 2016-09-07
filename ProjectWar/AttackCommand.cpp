//
//  AttackCommand.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 7/4/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#include "AttackCommand.h"
#include "Map.h"

AttackCommand::AttackCommand( const int unitID, const int targetID )
: unitID( unitID ), targetID( targetID ), mapContext( nullptr ) {

}

AttackCommand::AttackCommand( const AttackCommand& attackCommand )
: unitID( attackCommand.unitID ), targetID( attackCommand.targetID ),
 savedTarget( attackCommand.savedTarget ),
 savedUnit( attackCommand.savedUnit ),
 mapContext( attackCommand.mapContext ),
 savedUnitHP( attackCommand.savedUnitHP ),
 savedTargetHP( attackCommand.savedTargetHP ) {

}

Command& AttackCommand::clone() {
    return *new AttackCommand( *this );
}

void AttackCommand::execute( MapContext& context ) {
    if( mapContext != nullptr ) {
        throw IllegalStateException(
                            "Command state not restored after execution");
    }
    mapContext = &context;
    
    Unit* unit = mapContext->getEntity( unitID );
    Unit* targetUnit = mapContext->getEntity( targetID );
    
    savedUnit = unit;
    savedTarget = targetUnit;
    
    if( targetUnit != nullptr ) {
        savedUnitHP = unit->getHP();
        savedTargetHP = targetUnit->getHP();
        
        updateHP( unit, targetUnit );
        if ( targetUnit->getHP() <= 0 ) {
            targetUnit->setHP( 0 );
            targetUnit->updateState();
            mapContext->removeUnit( *targetUnit );
        }
        
        if( unit->getHP() <= 0 ) {
            unit->setHP( 0 );
            unit->updateState();
            mapContext->removeUnit( *unit );
        }
        
        updateHP( targetUnit, unit );
        if ( unit->getHP() <= 0 ) {
            unit->setHP( 0 );
            unit->updateState();
            mapContext->removeUnit( *unit );
        }
        
        if( targetUnit->getHP() <= 0 ) {
            targetUnit->setHP( 0 );
            targetUnit->updateState();
            mapContext->removeUnit( *targetUnit );
        }
    }
}

void AttackCommand::cancel() {
    if( savedTarget != nullptr ) {
        if( savedUnit->getHP() == 0 ) {
            mapContext->restoreUnit( *savedUnit );
        }
        
        if ( savedTarget->getHP() == 0 ) {
            mapContext->restoreUnit( *savedTarget );
        }
        savedUnit->setHP( savedUnitHP );
        savedTarget->setHP( savedTargetHP );

        savedUnit->updateState();
        savedTarget->updateState();
    }
    mapContext = nullptr;
    savedUnit = nullptr;
    savedTarget = nullptr;
}

void AttackCommand::updateHP( Unit* attacker, Unit* attacked ) {
    int damage = attacker->getHP() * 0.5;
    attacked->setHP( attacked->getHP() - damage );
}


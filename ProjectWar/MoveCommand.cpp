//
//  MoveCommand.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 21/3/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#include "MoveCommand.h"
#include "MapContext.h"
#include "GameException.h"

MoveCommand::MoveCommand( MapContext& mapContext,
                          const int unitID, const Point destination )
: executed( false ), unitID( unitID ), destination( destination )
, mapContext( mapContext ) {

}

MoveCommand::~MoveCommand() {

}

bool MoveCommand::changeContext( MapContext& mapContext ) {
    if( !executed ) {
        this->mapContext = mapContext;
        return true;
    }
    return false;
}

void MoveCommand::execute( ) {
    Unit* unit = mapContext.getEntity( unitID );
    savedPosition = unit->getPosition();
    
    if( executed ) {
        throw IllegalStateException( "Command state was not restored after execution" );
    }
    if( unit->getPosition() != savedPosition ) {
        throw IllegalStateException( "Illegal unit position modification" );
    }
    if( unit->getPosition().onRange(
                                    destination, unit->getMovement() ) ) {
        executed = true;
        mapContext.moveEntity( *unit, destination );
        unit->setPosition( mapContext.getTile( destination ) );
    }else {
        throw IllegalStateException( "Unit destination not on range" );
    }
}

void MoveCommand::cancel() {
    executed = false;
    Unit* unit = mapContext.getEntity( unitID );
    mapContext.moveEntity( *unit, savedPosition );
    unit->setPosition( mapContext.getTile( savedPosition ) );
}

const int MoveCommand::getUnitID() const {
    return unitID;
}

const Point& MoveCommand::getDestination() const {
    return destination;
}

bool MoveCommand::operator==( const MoveCommand& moveCommand ) const {
    if( destination == moveCommand.getDestination() ) {
        return true;
    }
    return false;
}
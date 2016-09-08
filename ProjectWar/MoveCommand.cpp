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

MoveCommand::MoveCommand( const int unitID, const Point destination )
: unitID( unitID ), destination( destination ),
 mapContext( nullptr ) {

}

MoveCommand::MoveCommand( const MoveCommand& moveCommand )
 : mapContext( moveCommand.mapContext ),
 unitID( moveCommand.unitID ), destination( moveCommand.destination ),
 savedPosition( moveCommand.savedPosition ) {

 }

MoveCommand::~MoveCommand() {

}

Command& MoveCommand::clone() {
    return *new MoveCommand( *this );
}

void MoveCommand::execute( MapContext& context ) {
    if( this->mapContext != nullptr ) {
        throw IllegalStateException( "Command state was not restored after execution" );
    }
    mapContext = &context;
    
    Unit* unit = mapContext->getEntity( unitID );
    savedPosition = unit->getPosition();
    
    if( unit->getPosition() != savedPosition ) {
        throw IllegalStateException( "Illegal unit position modification" );
    }
    if( unit->getPosition().onRange(
                                    destination, unit->getMovement() ) ) {
        mapContext->moveEntity( *unit, destination );
        unit->setPosition( mapContext->getTile( destination ) );
    }else {
        throw IllegalStateException( "Unit destination not on range" );
    }
}

void MoveCommand::cancel() {
    Unit* unit = mapContext->getEntity( unitID );
    mapContext->moveEntity( *unit, savedPosition );
    unit->setPosition( mapContext->getTile( savedPosition ) );
    mapContext = nullptr;
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
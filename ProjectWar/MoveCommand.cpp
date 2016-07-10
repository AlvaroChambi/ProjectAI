//
//  MoveCommand.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 21/3/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#include "MoveCommand.h"
#include "Map.h"
#include "OnMoveState.h"
#include "GameException.h"

MoveCommand::MoveCommand( Unit& unit, MapContext* map, const Point& destination ) {
    executed = false;
    this->unit = &unit;
    this->map = (Map*)map;
    this->savedPosition = unit.getTile();
    this->destination = this->map->getTile(destination);
}

MoveCommand::~MoveCommand() {

}

void MoveCommand::execute() {
    if( executed ) {
        throw IllegalStateException( "Command state was not restored after execution" );
    }
    if( unit->getPosition() != savedPosition.position ) {
        throw IllegalStateException( "Illegal unit position modification" );
    }
    if( unit->getPosition().onRange(
                            destination.position, unit->getMovement() ) ) {
        executed = true;
        map->moveEntity( *unit, destination.position );
        unit->setPosition( destination );
    }else {
        throw IllegalStateException( "Unit destination not on range" );
    }
}

void MoveCommand::cancel() {
    executed = false;
    map->moveEntity( *unit, savedPosition.position );
    unit->setPosition( savedPosition );
}
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

MoveCommand::MoveCommand( Unit* unit, IMap* map, const Point& destination ) {
    executed = false;
    this->unit = unit;
    this->map = (Map*)map;
    this->savedPosition = unit->getTile();
    this->destination = map->getTile(destination.x, destination.y);
}

MoveCommand::~MoveCommand() {

}

void MoveCommand::execute() {
    //TODO: Finish command error handling
    if( executed ) {
        throw IllegalStateException( "Command state was not restored after execution" );
    }
    if( unit->getPosition() != savedPosition.position ) {
        throw IllegalStateException( "Illegal unit position modification" );
    }
    if( unit->onRange( destination.position , unit->getMovement() ) ) {
        executed = true;
        map->moveUnit( unit, destination.position );
        unit->setPosition( destination );
    }else {
        throw IllegalStateException( "Unit destination not on range" );
    }
}

void MoveCommand::cancel() {
    executed = false;
    map->moveUnit( unit, savedPosition.position );
    unit->setPosition( savedPosition );
}
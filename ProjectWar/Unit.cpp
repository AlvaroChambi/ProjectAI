//
//  Unit.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 13/3/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#include "Unit.h"
#include "Map.h"
#include "Player.h"
#include "MoveCommand.h"
#include "AttackCommand.h"
#include "CaptureCommand.h"
#include "GameException.h"
#include "UnitFilter.h"
#include "AreaIterator.h"
#include "GameState.h"

Unit::Unit()
: Model(), tile(), movement( 0 ), hp( 0 ),
  active( true ), commands(), attackRange( 0 ), ownerID( -1 ) {
    
}

Unit::Unit( const Unit& unit ) {
    this->tile = unit.getTile();
    this->movement = unit.getMovement();
    this->hp = unit.getHP();
    this->attackRange = unit.getAttackRange();
    this->ownerID = unit.getOwnerID();
}

Unit::~Unit() {

}

//This method does not update the texture position, maybe we have to implement it
void Unit::setPosition( int x, int y ) {
    this->tile.position.x = x;
    this->tile.position.y = y;
}

void Unit::setPosition( const Tile tile ) {
    this->tile = tile;
    this->notifyObservers( POSITION_UPDATE );
}

void Unit::setMovement( int movement ) {
    this->movement = movement;
}

int Unit::getMovement() const {
    return movement;
}

void Unit::setActive( bool active ) {
    this->active = active;
    this->notifyObservers( ACTIVE_UPDATE );
}

bool Unit::isActive() const {
    return active;
}

void Unit::setSelected( bool selected ) {
    this->selected = selected;
    this->notifyObservers(SELECTED_UPDATE);
}

bool Unit::isSelected() const {
    return selected;
}

Tile Unit::getTile() const {
    return tile;
}

const Point Unit::getPosition() const {
    return tile.position;
}

void Unit::setAttackRange( int attackRange ) {
    this->attackRange = attackRange;
}

int Unit::getAttackRange() const {
    return attackRange;
}

void Unit::setHP( int hp )  {
    this->hp = hp;
    this->notifyObservers( HP_UPDATE );
}

int Unit::getHP() const {
    return hp;
}

void Unit::updateCommands( std::vector<UnitCommand> commands ) {
    //Clean previous commands and set the new ones
    this->commands = commands;
    this->notifyObservers( COMMANDS_UPDATE );
}

void Unit::addCommand( UnitCommand command ) {
    commands.push_back(command);
}

UnitCommand Unit::getCommand( int position ) const {
    return commands.at( position  );
}

int Unit::getNumCommands() const {
    return (int)commands.size();
}

void Unit::updateState() {
    this->notifyObservers(STATE_UPDATE);
}

void Unit::setOwnerID( int ownerID ) {
    this->ownerID = ownerID;
}

int Unit::getOwnerID() const {
    return ownerID;
}
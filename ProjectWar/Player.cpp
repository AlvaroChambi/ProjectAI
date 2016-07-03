//
//  Player.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 13/3/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#include "Player.h"
#include "Map.h"
#include <string>

Player::Player()
: Model(), selectedUnit( nullptr ),
active( false ), map( nullptr ), type( HUMAN_PLAYER ),
headquarter( nullptr ) {
    
}

Player::Player( int id )
: Player() {
    this->setid(id);
}

Player::~Player() {

}

void Player::addUnit( int unitReference ) {
    Unit* unit = map->getEntity( unitReference );
    unit->setOwnerID( getId() );
    army.push_back( unitReference );
}

Unit* Player::getUnit( int id ) const {
    Unit* result = nullptr;
    for ( int reference : army ) {
        Unit* unit = map->getEntity( reference );
        if( unit != nullptr && unit->getId() == id ) {
            result = unit;
        }
    }
    return result;
}

std::vector<Unit*> Player::getUnits() const {
    std::vector<Unit*> units;
    for ( int reference : army ) {
        Unit* unit = map->getEntity( reference );
        if( unit != nullptr ) {
            units.push_back( unit );
        }
    }
    return units;
}

void Player::setSelectedUnit( Unit *unit ) {
    if( unit != nullptr ) {
        unit->setSelected( true );
    }else {
        this->selectedUnit->setSelected( false );
    }
    this->selectedUnit = unit;
    this->notifyObservers( SELECTED_UPDATE );
    
}

Unit* Player::getSelectedUnit() const {
    return selectedUnit;
}

State* Player::getState() const {
    return state;
}

void Player::setMap( Map *map ) {
    this->map = map;
}

Map* Player::getMap() const {
    return map;
}

void Player::setType( PlayerType type ) {
    this->type = type;
}

PlayerType Player::getType() const {
    return type;
}

//Update the player actual state and enter in it
void Player::updateState( State *state ) {
    this->state = state;
    this->state->enter();
}

void Player::setState( State *state ) {
    this->state = state;
}

void Player::setActive( bool active ) {
    this->active = active;
    this->notifyObservers( ACTIVE_UPDATE );
}

bool Player::isActive() const {
    return active;
}

bool Player::hasUnit( int id ) const {
    bool result = false;
    for ( int reference : army ) {
        Unit* unit = map->getEntity( reference );
        if( unit != nullptr && unit->getId() == id ) {
            result = true;
        }
    }
    return result;
}

bool Player::hasUnitAlive() const {
    bool result = false;
    for ( int reference : army ) {
        Unit* unit = map->getEntity( reference );
        if ( unit != nullptr && unit->getHP() > 0 ) {
            result = true;
        }
    }
    return result;
}

bool Player::hasCapturedHQ( Player* enemy ) {
    Building* enemyHQ = enemy->getHeadquarter();
    return enemyHQ->isCaptured( getId() );
}

Building* Player::getHeadquarter() {
    return headquarter;
}

void Player::setHeadquarter( Building *headquarter ) {
    this->headquarter = headquarter;
}
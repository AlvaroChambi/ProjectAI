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
headquarter( -1 ) {
    
}

Player::Player( int id )
: Player() {
    this->setid(id);
}

Player::Player( const Player& player ) {
    this->army = player.army;
    this->headquarter = player.headquarter;
    this->setid( player.getId() );
}

Player::~Player() {
    army.clear();
}

void Player::addUnit( Unit& unit ) {
    unit.setOwnerID( getId() );
    army.push_back( unit.getId() );
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
    units.reserve( army.size() );
    for ( int reference : army ) {
        Unit* unit = map->getEntity( reference );
        if( unit != nullptr ) {
            units.push_back( unit );
        }
    }
    return units;
}

std::vector<int> Player::getUnitsReference() const {
    return army;
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

void Player::setMap( MapContext* map ) {
    this->map = map;
}

MapContext* Player::getMap() const {
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
        if( reference == id ) {
            result = true;
        }
    }
    return result;
}

bool Player::hasUnitAlive() const {
    bool result = false;
    for ( int reference : army ) {
        Unit* unit = map->getEntity( reference );
        if ( unit != nullptr ) {
            return true;
        }
    }
    return result;
}

bool Player::hasCapturedHQ( const Player& enemy ) const {
    Building* enemyHQ = enemy.getHeadquarter();
    return enemyHQ->isCaptured( getId() );
}

Building* Player::getHeadquarter() const {
    return map->getStructure( headquarter );
}

void Player::setHeadquarter( int id ) {
    this->headquarter = id;
}

std::vector<Building*> Player::getStructures() const {
    std::vector<Building*> structures = map->getStructures();
    std::vector<Building*> playerStructures;
    for( Building* building : structures ) {
        if( building->getId() == getId() ) {
            playerStructures.push_back( building );
        }
    }
    return playerStructures;
}
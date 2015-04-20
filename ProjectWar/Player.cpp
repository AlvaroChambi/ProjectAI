//
//  Player.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 13/3/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#include "Player.h"
#include "Map.h"

Player::Player() : Model(), position(0,0), selectedUnit(nullptr),
                    active(false), map(nullptr), type(HUMAN_PLAYER)
{
    
}

Player::Player(int id) : Model(), position(0,0), selectedUnit(nullptr),
                        active(false), map(nullptr)
{
    this->setid(id);
}

Player::~Player()
{

}

void Player::setPosition(int x, int y)
{
    position.x = x;
    position.y = y;
    this->notifyObservers(POSITION_UPDATE);
}

Point Player::getPosition()
{
    return position;
}

void Player::setTile(const Tile tile)
{
    this->tile = tile;
    this->notifyObservers(POSITION_UPDATE);
}

Tile Player::getTile()
{
    return tile;
}

void Player::addUnit(Unit *unit)
{
    units.add(unit);
}

Unit* Player::getUnit(int id)
{
    Unit* unit = nullptr;
    for (int i = 0; i < units.getSize(); i++) {
        if (units.getElement(i)->getId() == id) {
            unit = units.getElement(i);
        }
    }
    return unit;
}

List<Unit*>& Player::getUnitList()
{
    return this->units;
}

//Update the unit selected flag and the player reference to the unit
//nullptr if there isn't any unit selected
void Player::setSelectedUnit(Unit *unit)
{
    if(unit != nullptr){
        unit->setSelected(true);
    }else{
        this->selectedUnit->setSelected(false);
    }
    this->selectedUnit = unit;
    this->notifyObservers(SELECTED_UPDATE);
    
}

Unit* Player::getSelectedUnit()
{
    return selectedUnit;
}

State* Player::getState()
{
    return state;
}

void Player::setMap(Map *map)
{
    this->map = map;
}

Map* Player::getMap()
{
    return map;
}

void Player::setType(PlayerType type)
{
    this->type = type;
}

PlayerType Player::getType()
{
    return type;
}

//Update the player actual state and enter in it
void Player::updateState(State *state)
{
    this->state = state;
    this->state->enter();
}

void Player::setState(State *state)
{
    this->state = state;
}

void Player::setActive(bool active)
{
    this->active = active;
    this->notifyObservers(ACTIVE_UPDATE);
}

bool Player::isActive()
{
    return active;
}

bool Player::hasUnit(int id)
{
    bool result = false;
    for (int i = 0; i < units.getSize(); i++) {
        if(units.getElement(i)->getId() == id){
            result = true;
        }
    }
    return result;
}

void Player::populateInfoMap(InfoMap& infoMap)
{
    //Maybe place this code in the Map
    for (int i = 0; i < units.getSize(); i++) {
        Unit* unit = units.getElement(i);
        Point position = unit->getPosition();
        InfoTile* tile = infoMap[position.x][position.y];
        tile->entity = UNIT_ENTITY;
        tile->ownerID = getId();
        tile->unitID = unit->getId();
        tile->text->setTextResource("Unit: " + std::to_string(tile->ownerID)+"-"+std::to_string(tile->unitID));
        
    }
}
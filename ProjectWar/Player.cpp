//
//  Player.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 13/3/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#include "Player.h"
#include "Map.h"
#include "MessageManager.h"

Player::Player() : Model(), position(0,0), selectedUnit(nullptr),
                    active(false), map(nullptr), type(HUMAN_PLAYER), color(nullptr)
{
    setFounds(3000);
}

Player::Player(int id) : Model(), position(0,0), selectedUnit(nullptr),
                        active(false), map(nullptr), type(HUMAN_PLAYER),color(nullptr)
{
    setFounds(3000);
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

void Player::setFounds(int founds)
{
    this->founds = founds;
    MessageManager::getInstance().sendMessage(new Message(MESSAGE_UPDATE_PLAYER_INFO));
}

int Player::getFounds()
{
    return founds;
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
    units.push_back(unit);
}

Unit* Player::getUnit(int id)
{
    Unit* result = nullptr;
    for (Unit* unit : units) {
        if (unit->getId() == id) {
            result = unit;
        }
    }
    return result;
}

std::list<Unit*>& Player::getUnitList()
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

void Player::setColor(Color* color)
{
    this->color = color;
}

Color* Player::getColor()
{
    return color;
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

bool Player::hasBuilding(int id)
{
    bool result = false;
    Building* building = map->getBuilding(id);
    if(building->getOwnerID() == getId()){
        return true;
    }
    return result;
}

bool Player::hasUnit(int id)
{
    bool result = false;
    for (Unit* unit : units) {
        if(unit->getId() == id){
            result = true;
        }
    }
    return result;
}

bool Player::hasUnitAlive()
{
    bool result = false;
    for (Unit* unit : units) {
        if (unit->getHP() > 0) {
            result = true;
        }
    }
    return result;
}

bool Player::hasCapturedHQ()
{
    bool result = true;
    for (Building* building : map->getBuildings()) {
        if (building->getOwnerID() != getId() || building->getCaptureValue() < building->getCapturePoints()) {
            //as soon as we find a build that isn't captured for the player set the flag to false
            result = false;
        }
    }
    return result;
}

void Player::populateInfoMap(InfoMap& infoMap)
{
    //Maybe place this code in the Map
    for (Unit* unit : units) {
        Point position = unit->getPosition();
        InfoTile* tile = infoMap[position.x][position.y];
        tile->entity = UNIT_ENTITY;
        tile->ownerID = getId();
        tile->unitID = unit->getId();
        tile->text->setTextResource("Unit: " + std::to_string(tile->ownerID)+"-"+std::to_string(tile->unitID));
        
    }
}
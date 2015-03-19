//
//  Player.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 13/3/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#include "Player.h"

Player::Player() : Model(), position(0,0), numUnits(0), selectedUnit(nullptr)
{
    
}

Player::~Player()
{

}

void Player::setPosition(int x, int y)
{
    position.x = x;
    position.y = y;
    this->notifyObservers();
}

Point Player::getPosition()
{
    return position;
}

void Player::setTile(const Tile tile)
{
    this->tile = tile;
    this->notifyObservers();
}

Tile Player::getTile()
{
    return tile;
}

void Player::addUnit(Unit *unit)
{
    units[numUnits] = unit;
    numUnits++;
}

Unit* Player::getUnit(int id)
{
    Unit* unit = nullptr;
    for (int i = 0; i < numUnits; i++) {
        if (units[i]->getId() == id) {
            unit = units[i];
        }
    }
    return unit;
}

void Player::setSelectedUnit(Unit *unit)
{
    this->selectedUnit = unit;
}

Unit* Player::getSelectedUnit()
{
    return selectedUnit;
}

State* Player::getState()
{
    return state;
}

//Update the player actual state and enter in it
void Player::updateState(State *state)
{
    this->state = state;
    this->state->enter();
}
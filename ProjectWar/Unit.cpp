//
//  Unit.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 13/3/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#include "Unit.h"

Unit::Unit() : Model(), tile(), movement(0), hp(0), active(true)
{
    
}

Unit::~Unit()
{

}

//This method does not update the texture position, maybe we have to implement it
void Unit::setPosition(int x, int y)
{
    this->tile.position.x = x;
    this->tile.position.y = y;
}

void Unit::setPosition(const Tile tile)
{
    this->tile = tile;
    this->notifyObservers(POSITION_UPDATE);
}

void Unit::setMovement(int movement)
{
    this->movement = movement;
}

int Unit::getmovement()
{
    return movement;
}

void Unit::setActive(bool active)
{
    this->active = active;
    this->notifyObservers(ACTIVE_UPDATE);
}

bool Unit::isActive()
{
    return active;
}

void Unit::setSelected(bool selected)
{
    this->selected = selected;
    this->notifyObservers(SELECTED_UPDATE);
}

bool Unit::isSelected()
{
    return selected;
}

bool Unit::canReach(Point destination)
{
    bool result = false;
    int distance = std::abs(destination.x - this->getPosition().x) +
                    std::abs(destination.y - this->getPosition().y);
    if (distance <= movement) {
        result = true;
    }
    return result;
}

Tile Unit::getTile()
{
    return tile;
}

Point Unit::getPosition()
{
    return tile.position;
}

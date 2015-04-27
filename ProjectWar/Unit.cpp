//
//  Unit.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 13/3/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#include "Unit.h"

Unit::Unit() : Model(), tile(), movement(0), hp(0), active(true), commands(), attackRange(0)
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

int Unit::getMovement()
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

Tile Unit::getTile()
{
    return tile;
}

Point Unit::getPosition()
{
    return tile.position;
}

void Unit::setAttackRange(int attackRange)
{
    this->attackRange = attackRange;
}

int Unit::getAttackRange()
{
    return attackRange;
}

void Unit::setHP(int hp)
{
    this->hp = hp;
    this->notifyObservers(HP_UPDATE);
}

int Unit::getHP()
{
    return hp;
}

void Unit::updateCommands(List<UnitCommand> commands)
{
    //Clean previous commands and set the new ones
    this->commands = commands;
    this->notifyObservers(COMMANDS_UPDATE);
}

void Unit::addCommand(UnitCommand command)
{
    commands.add(command);
}

UnitCommand Unit::getCommand(int position)
{
    return commands.getElement(position);
}

int Unit::getNumCommands()
{
    return commands.getSize();
}

//TODO duplicated code here...
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

bool Unit::canAttack(Point destination)
{
    bool result = false;
    int distance = std::abs(destination.x - this->getPosition().x) +
                    std::abs(destination.y - this->getPosition().y);
    
    if (distance <= attackRange) {
        result = true;
    }
    return result;
}

//Movement added to the attack to know if the unit can attack the targeted unit in this turn
bool Unit::canAttack(Unit* unit)
{
    bool result;
    Point destination = unit->getPosition();
    int distance = std::abs(destination.x - this->getPosition().x) +
    std::abs(destination.y - this->getPosition().y);
    
    if (distance <= attackRange + movement) {
        result = true;
    }
    return result;
}

void Unit::updateState()
{
    this->notifyObservers(STATE_UPDATE);
}
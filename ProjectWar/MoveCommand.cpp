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

MoveCommand::MoveCommand(Unit* unit,Map* map ,Tile destination)
{
    this->unit = unit;
    this->map = map;
    this->savedPosition = unit->getTile();
    this->destination = destination;
}

MoveCommand::~MoveCommand()
{

}

void MoveCommand::execute()
{
    std::cout << "executing move command\n";
    map->cleanUnitAvailableArea(unit);
    map->moveUnit(unit, destination.position);
    unit->setPosition(destination);
}

void MoveCommand::cancel()
{
    std::cout << "canceling move command\n";
    map->moveUnit(unit, savedPosition.position);
    unit->setPosition(savedPosition);
}
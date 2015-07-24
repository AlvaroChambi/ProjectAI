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

MoveCommand::MoveCommand(Unit* unit,Map* map ,Point destination)
{
    this->unit = unit;
    this->map = map;
    this->savedPosition = unit->getTile();
    this->destination = map->getTile(destination.x, destination.y);
}

MoveCommand::~MoveCommand()
{

}

void MoveCommand::execute()
{
  //  std::cout << "              executing move command\n";
  //  std::cout <<"                   unit: " + std::to_string(unit->getId()) <<  "  " << destination.position << "\n";
    map->cleanUnitAvailableArea(unit);
    map->moveUnit(unit, Point(destination.column, destination.row));
    unit->setPosition(destination);
}

void MoveCommand::cancel()
{
    std::cout << "              canceling move command\n";
    std::cout <<"                   unit: " + std::to_string(unit->getId()) + "\n";
    map->moveUnit(unit, Point(savedPosition.row, savedPosition.column));
    unit->setPosition(savedPosition);
}
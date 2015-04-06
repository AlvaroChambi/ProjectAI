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

MoveCommand::MoveCommand(Player* player, Tile destination)
{
    this->player = player;
    this->savedPosition = player->getSelectedUnit()->getTile();
    this->destination = destination;
    this->savedState = player->getState();
}

MoveCommand::~MoveCommand()
{

}

void MoveCommand::execute()
{
    std::cout << "executing move command\n";
    Unit* unit = player->getSelectedUnit();
    player->getMap()->cleanUnitAvailableArea(player->getSelectedUnit());
    player->getMap()->moveUnit(unit, destination.position);
    unit->setPosition(destination);
    player->updateState(new OnMoveState(player, this));
}

void MoveCommand::cancel()
{
    std::cout << "canceling move command\n";
    Unit* unit = player->getSelectedUnit();
    player->getMap()->moveUnit(unit, savedPosition.position);
    unit->setPosition(savedPosition);
    player->updateState(savedState);
}
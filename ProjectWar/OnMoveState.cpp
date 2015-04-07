//
//  OnMoveState.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 29/3/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#include "OnMoveState.h"
#include "Player.h"
#include "Map.h"

OnMoveState::OnMoveState(Model* model, Command* command) : OnCommandState(model, command)
{

}

OnMoveState::~OnMoveState()
{

}

void OnMoveState::enter()
{
    Player* player = (Player*)model;
    Unit* unit = player->getSelectedUnit();
    List<UnitCommand> commands;
    commands.add(CANCEL);
    commands.add(WAIT);
    //Check if there are any enemy aroud
    player->getMap()->checkNearEntities(unit,commands);
    //update commands
    unit->updateCommands(commands);
}

void OnMoveState::handleInput(Input input, int id, Tile position)
{
    OnCommandState::handleInput(input, id, position);
    switch (input) {
        //just do nothing, i think...
        default:
            break;
    }
}
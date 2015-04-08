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
#include "OnAttackState.h"
#include "AttackCommand.h"

OnMoveState::OnMoveState(Model* model,State* savedState, Command* command)
                        : OnCommandState(model, savedState,command)
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
    Player* player = (Player*)model;
    OnCommandState::handleInput(input, id, position);
    switch (input) {
        case ATTACK_CLICKED:
        {
            Unit* unit = player->getSelectedUnit();
            //TODO At this point i should have and enemy unit, but i don't know how...
            Command* attackCommand = new AttackCommand(unit, nullptr);
            attackCommand->execute();
            player->updateState(new OnAttackState(player, player->getState(), attackCommand));
        }
            break;
        default:
            break;
    }
}
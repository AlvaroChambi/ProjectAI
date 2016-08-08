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
#include "CaptureCommand.h"

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
    std::vector<UnitCommand> commands;
    commands.push_back(CANCEL);
    commands.push_back(WAIT);
    //Check if there are any enemy aroud
    Map* map = (Map*)player->getMap();
    map->checkNearEntities( *unit,commands );
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
            //TODO pretty much the same code here and in OnMovedState attack event
            player->updateState(new OnAttackState(player, player->getState()));
        }
            break;
        case CAPTURE_CLICKED:
        {
            executeCommand(new CaptureCommand(
                                    player->getSelectedUnit()->getId() ));
            OnCommandState::handleInput(WAIT_CLICKED, -1, nullptr);
        }
            break;
        default:
            break;
    }
}
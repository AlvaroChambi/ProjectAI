//
//  OnAttackState.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 29/3/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#include "OnAttackState.h"
#include "player.h"
#include "Map.h"

OnAttackState::OnAttackState(Model* model, State* savedState, Command* command)
                            : OnCommandState(model, savedState, command)
{

}

OnAttackState::~OnAttackState()
{

}

void OnAttackState::enter()
{
    Player* player = (Player*)model;
    Unit* unit = player->getSelectedUnit();
    //Update unit commands
    List<UnitCommand> commands;
    commands.add(CANCEL);
    commands.add(ATTACK);
    unit->updateCommands(commands);
}

void OnAttackState::handleInput(Input input, int id, Tile position)
{
    OnCommandState::handleInput(input, id, position);
    switch (input) {
        case ATTACK_CLICKED:
            //go to a clean state
            OnCommandState::handleInput(WAIT_CLICKED, id, position);
            break;
        case ENEMY_UNIT_CLICKED:
            //if can reach target selected enemy
            //update attack results(maybe cancel previous executed attack command)
            
            //attack command execute
            break;
        default:
            break;
    }
}
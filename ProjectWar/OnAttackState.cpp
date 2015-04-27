//
//  OnAttackState.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 29/3/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#include "OnAttackState.h"
#include "Player.h"
#include "Map.h"
#include "AttackCommand.h"

OnAttackState::OnAttackState(Model* model, State* savedState)
                            : OnCommandState(model, savedState, nullptr), targetUnit(nullptr)
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
    Player* player = (Player*)model;
    OnCommandState::handleInput(input, id, position);
    switch (input) {
        case ATTACK_CLICKED:
            //go to a clean state
            OnCommandState::handleInput(WAIT_CLICKED, id, position);
            //TODO just allow attack if a command has already been executed
            //clean all unit resource if the unit hp is 0
            //Add this behaviour in the command attack
            this->targetUnit->updateState();
            if(targetUnit->getHP() == 0){
                player->getMap()->removeUnit(targetUnit);
            }
            break;
        default:
            break;
    }
}

void OnAttackState::handleInput(Input input, int id, Tile position, Unit* targetUnit)
{
    Player* player = (Player*) model;
    OnCommandState::handleInput(input, id, position);
    switch (input) {
        case ENEMY_UNIT_CLICKED:
        {
            //if can reach target selected enemy
            if (player->getSelectedUnit()->canAttack(targetUnit->getPosition())) {
                //Move target tile over the attacked unit
                player->setTile(player->getMap()->getTile(targetUnit->getPosition().x, targetUnit->getPosition().y));
                this->targetUnit = targetUnit;
                //cancel previous executed command if there is one(Once cancelled the command is set to null)
                this->cancelCommand();
                executeCommand(new AttackCommand(player->getSelectedUnit(), targetUnit));
            }
            break;
        }
        default:
            break;
    }

}
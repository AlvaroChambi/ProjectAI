//
//  UnitSelectedState.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 19/3/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#include "UnitSelectedState.h"
#include "Map.h"
#include "OnAttackState.h"
#include "OnMoveState.h"
#include "MoveCommand.h"

UnitSelectedState::UnitSelectedState(Player* player) : State(player)
{

}

UnitSelectedState::~UnitSelectedState()
{

}

void UnitSelectedState::enter()
{
    //TODO refactor state class to avoid implicit cast here...
    Player* player = (Player*)model;
    Unit* unit = player->getSelectedUnit();
    //Update available area and set unit as selected
    player->getMap()->updateUnitAvailableArea(unit);
    List<UnitCommand> commands;
    commands.add(WAIT);
    //Check if there are any unit around
    player->getMap()->checkNearEntities(unit, commands);
    //Update commands
    player->getSelectedUnit()->updateCommands(commands);
}

void UnitSelectedState::handleInput(Input input, int id, Tile position)
{
    Player* player = (Player*)model;
    switch (input) {
        case UNIT_CLICKED:
        {
            //Select new unit - keep state
            Unit* unit = player->getUnit(id);
            player->getMap()->cleanUnitAvailableArea(unit);
            player->setSelectedUnit(unit);
            player->getState()->enter();
        }
            break;
        case MAP_CLICKED:
        {
            Unit* unit = player->getSelectedUnit();
            
            if (unit->canReach(position.position)) {
                Command* moveCommand = new MoveCommand(player, position);
                moveCommand->execute();
            }else{
                player->setTile(position);
                player->updateState(new NothingSelectedState(player));
            }
        }
            break;
        case ATTACK_CLICKED:
        {

        }
            break;
        case WAIT_CLICKED:
        {
            player->getSelectedUnit()->setActive(false);
            player->updateState(new NothingSelectedState(player));
        }
            break;
        default:
            break;
    }
}
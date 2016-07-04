//
//  NothingSelectedState.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 19/3/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#include "NothingSelectedState.h"
#include "Map.h"

NothingSelectedState::NothingSelectedState(Player* player) : State(player)
{

}

NothingSelectedState::~NothingSelectedState()
{

}

void NothingSelectedState::enter()
{
    Player* player = (Player*)model;
    player->getMap()->cleanUnitAvailableArea(*player->getSelectedUnit());
    std::vector<UnitCommand> commands;
    commands.push_back(END);
    player->getSelectedUnit()->updateCommands(commands);
    player->setSelectedUnit(nullptr); //Nothing selected
}

void NothingSelectedState::handleInput(Input input, int id, Tile position)
{
    switch (input) {
        case UNIT_CLICKED:
        {
            //Selected unit - update state
            Player* player = (Player*)model;
            Unit* unit = player->getUnit(id);
            player->setSelectedUnit(unit);
            
            player->updateState(new UnitSelectedState(player));
        }
            break;
        case MAP_CLICKED:
        {

        }
            break;
        case ENEMY_UNIT_CLICKED:
        {
        }
        default:
            break;
    }
}
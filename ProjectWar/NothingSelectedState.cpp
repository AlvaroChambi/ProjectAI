//
//  NothingSelectedState.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 19/3/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#include "NothingSelectedState.h"
#include "FactorySelectedState.h"
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
    //TODO bad acces when entering this state with no unit selected
    player->getMap()->cleanUnitAvailableArea(player->getSelectedUnit());
    std::list<UnitCommand> commands;
    commands.push_back(END);
    player->getSelectedUnit()->updateCommands(commands);
    player->setSelectedUnit(nullptr); //Nothing selected
}

void NothingSelectedState::handleInput(Input input, int id, Tile position)
{
    Player* player = (Player*)model;
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
            //Move player - keep state
            player->setTile(position);
        }
            break;
        case ENEMY_UNIT_CLICKED:
        {
        }
            break;
        case BUILDING_CLICKED:
        {
            std::cout << "Building clicked: " << std::to_string(id) << std::endl;
            Building* building = player->getMap()->getBuilding(id);
           
            if (building->getType() == "Factory" && player->hasBuilding(id)) {
                player->updateState(new FactorySelectedState(player));
            }
        }
            break;
        default:
            break;
    }
}
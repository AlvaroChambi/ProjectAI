//
//  NothingSelectedState.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 19/3/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#include "NothingSelectedState.h"

NothingSelectedState::NothingSelectedState(Player* player) : State(player)
{

}

NothingSelectedState::~NothingSelectedState()
{

}

void NothingSelectedState::enter()
{
    std::cout << "getting into NothingSelectedState...\n";
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
            //Move player - keep state
            Player* player = (Player*)model;
            player->setTile(position);
        }
            break;
        default:
            break;
    }
}
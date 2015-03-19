//
//  UnitSelectedState.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 19/3/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#include "UnitSelectedState.h"

UnitSelectedState::UnitSelectedState(Player* player) : State(player)
{

}

UnitSelectedState::~UnitSelectedState()
{

}

void UnitSelectedState::enter()
{
    std::cout << "getting into UnitSelectedState...\n";
}

void UnitSelectedState::handleInput(Input input, int id, Tile position)
{
    switch (input) {
        case UNIT_CLICKED:
        {
            //Select new unit - keep state
            Player* player = (Player*)model;
            Unit* unit = player->getUnit(id);
            player->setSelectedUnit(unit);
        }
            break;
        case MAP_CLICKED:
        {
            //update state
            Player* player = (Player*)model;
            Unit* unit = player->getSelectedUnit();
            unit->setPosition(position);
        }
            break;
        default:
            break;
    }
}
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
    //TODO refactor state class to avoid implicit cast here...
    Player* player = (Player*)model;
    
    //Update available area and set unit as selected
    player->getMap()->updateUnitAvailableArea(player->getSelectedUnit());
}

void UnitSelectedState::handleInput(Input input, int id, Tile position)
{
    switch (input) {
        case UNIT_CLICKED:
        {
            //Select new unit - keep state
            Player* player = (Player*)model;
            Unit* unit = player->getUnit(id);
            player->getMap()->cleanUnitAvailableArea(unit);
            player->setSelectedUnit(unit);
            player->getState()->enter();
        }
            break;
        case MAP_CLICKED:
        {
            Player* player = (Player*)model;
            Unit* unit = player->getSelectedUnit();
            
            if (unit->canReach(position.position)) {
                //new MoveCommand(unit).execute// command just executes if unit is active?
                player->getMap()->cleanUnitAvailableArea(unit);
                unit->setPosition(position);
                unit->setActive(false);
                player->updateState(new NothingSelectedState(player));
            }else{
                player->setTile(position);
                player->getMap()->cleanUnitAvailableArea(player->getSelectedUnit());
                player->updateState(new NothingSelectedState(player));
            }
        }
            break;
        default:
            break;
    }
}
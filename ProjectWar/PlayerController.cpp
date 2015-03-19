//
//  PlayerController.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 15/3/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#include "PlayerController.h"

PlayerController::PlayerController() : player(nullptr)
{
    
}

PlayerController::~PlayerController()
{

}

void PlayerController::setPlayer(Player *player)
{
    this->player = player;
    player->updateState(new NothingSelectedState(player));
}

void PlayerController::onMapClicked(const Tile tile)
{
    //ID not needed
    player->getState()->handleInput(MAP_CLICKED, -1, tile);
}

void PlayerController::onUnitClicked(const int id)
{
    //Position not needed
    player->getState()->handleInput(UNIT_CLICKED, id, nullptr);
}

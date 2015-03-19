//
//  PlayerController.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 15/3/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#include "PlayerController.h"

PlayerController::PlayerController()
{
    player = nullptr;
}

PlayerController::~PlayerController()
{

}

void PlayerController::setPlayer(Player *player)
{
    this->player = player;
}

void PlayerController::onMapClicked(const Tile tile)
{
    //std::cout << "PlayerController\n";
    //std::cout << "map clicked: " << tile.position.x << " " << tile.position.y << "\n";
    player->setTile(tile);
    
}

void PlayerController::onUnitClicked(const int id)
{
    std::cout << "unit clicked: ";
    Unit* unit = player->getUnit(id);
    if(unit != nullptr){
        std::cout << unit->getId() << " resource: " << unit->getResource() << "\n";
    }
}

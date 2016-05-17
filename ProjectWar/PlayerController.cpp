//
//  PlayerController.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 15/3/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#include "PlayerController.h"
#include "ProjectAI.h"

PlayerController::PlayerController() : player(nullptr)
{
    unitClicked=false;
}

PlayerController::~PlayerController()
{

}

void PlayerController::setPlayer(Player *player)
{
    this->player = player;
    player->setState(new NothingSelectedState(player));
}

bool PlayerController::getUnitCurrentlyClicked()
{
    return unitClicked;
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
    unitClicked=true;
}

void PlayerController::onEnemyUnitClicked(Unit* targetUnit)
{
    //Position not needed
    std::cout << "onEnemyUnitClicked\n";
    //here i can get a enemy unit
    player->getState()->handleInput(ENEMY_UNIT_CLICKED, -1, nullptr, targetUnit);
}

void PlayerController::onUIEventReceived(int id)
{
    //Just input needed
    unitClicked=false;
    switch (id) {
        case ProjectAI::WAIT_BUTTON:
            player->getState()->handleInput(WAIT_CLICKED, -1,nullptr);
            break;
        case ProjectAI::CANCEL_BUTTON:
            player->getState()->handleInput(CANCEL_CLICKED, -1,nullptr);
            break;
        case ProjectAI::ATTACK_BUTTON:
            //here i would need an enemy unit(but i don't know which one of them)
            player->getState()->handleInput(ATTACK_CLICKED, -1,nullptr);
            break;
        case ProjectAI::CAPTURE_BUTTON:
            player->getState()->handleInput(CAPTURE_CLICKED, -1, nullptr);
            break;
        default:
            break;
    }
}

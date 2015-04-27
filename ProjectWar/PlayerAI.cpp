//
//  PlayerAI.cpp
//  ProjectWar
//
//  Created by Pablo Luis Gutierrez on 09/04/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#include "PlayerAI.h"
#include "Map.h"
#include "TacticMinimax.h"

PlayerAI::PlayerAI() : Player(), playersList(nullptr)
{
    setType(AI_PLAYER);
}

PlayerAI::PlayerAI(int id) : Player(id), playersList(nullptr)
{
    setType(AI_PLAYER);
}

PlayerAI::~PlayerAI()
{

}

void PlayerAI::setPlayerList(List<Player*> *players)
{
    this->playersList = players;
}

List<Command*> PlayerAI::play()
{
    List<Command*>* commands = new List<Command*>;
    Player* enemy = nullptr;
    
    for (int i = 0; i < playersList->getSize(); i++) {
        Player* player = playersList->getElement(i);
        if (this->getId() != player->getId()) {
            enemy = player;
        }
    }
    GameState* game = new GameState(this, enemy);
    TacticMinimax* tacticDecision = new TacticMinimax(*game);
    
    tacticDecision->minimax(10);
    Tactic* movement = (Tactic*)tacticDecision->getMove();
    
    movement->execute();
    return *commands;
}
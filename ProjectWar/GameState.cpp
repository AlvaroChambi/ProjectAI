//
//  GameState.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 25/4/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#include "GameState.h"

GameState::GameState(Player* player, Player* enemy) : player(player), enemy(enemy)
{

}

GameState::~GameState()
{

}

bool GameState::isGameOver()
{
    bool result = false;
    if (!player->hasUnitAlive() || enemy->hasCapturedHQ()) {
        result = true;
    }
    if (!enemy->hasUnitAlive() || player->hasCapturedHQ()) {
        result = true;
    }
    
    return result;
}

int GameState::getStaticEvaluation()
{
    int result = DRAW_VALUE;
    for (int i = 0; i < player->getUnitList().getSize(); i++) {
        Unit* unit = player->getUnitList().getElement(i);
        result = result + unit->getHP() * 0.1;
    }
    
    for (int i = 0; i < enemy->getUnitList().getSize(); i++) {
        Unit* unit = player->getUnitList().getElement(i);
        result = result - unit->getHP() * 0.1;
    }

    return result;
}

void GameState::processMove(Option *move)
{
    std::cout << "//////////////MOVE FORWARD//////////\n";
    std::cout << "Option executed \n";
    move->execute();
}

void GameState::unprocessMove(Option *move)
{
    std::cout << "Option canceled \n";
    move->cancel();
}
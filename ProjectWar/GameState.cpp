//
//  GameState.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 25/4/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#include "GameState.h"

GameState::GameState(Player* player, Player* enemy, Scene* scene, Renderer* renderer)
        :player(player),
        enemy(enemy),
        scene(scene),
        renderer(renderer)
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
    Point point;
    int result = DRAW_VALUE;
    for (Unit* unit : player->getUnitList()) {
        point.x = 2;
        point.y = 2;
        result = result + unit->getHP() * 0.1;
        result = result - unit->getPosition().distance(point);

    }
    
    for (Unit* unit : enemy->getUnitList()) {
        point.x = 12;
        point.y = 6;
        result = result - unit->getHP() * 0.1;
        result = result + unit->getPosition().distance(point);
    }

    return result;
}

void GameState::processMove(Option *move) {
    move->execute();
}

void GameState::unprocessMove(Option *move) {
    move->cancel();
}
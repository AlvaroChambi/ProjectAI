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
    int result = DRAW_VALUE;
    for (Unit* unit : player->getUnitList()) {
        result = result + unit->getHP() * 0.1;
    }
    
    for (Unit* unit : enemy->getUnitList()) {
        result = result - unit->getHP() * 0.1;
    }

    return result;
}

void GameState::processMove(Option *move)
{
    std::cout << "//////////////MOVE FORWARD//////////\n";
    std::cout << "Option executed \n";
    move->execute();
    //TODO Minimax debug : remove
    renderer->renderClear();
    scene->render();
    renderer->renderPresent();
}

void GameState::unprocessMove(Option *move)
{
    std::cout << "Option canceled \n";
    move->cancel();
}
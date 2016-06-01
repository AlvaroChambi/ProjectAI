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

void calculateBuildingsHealth(Building* playerBuilding, Building* enemyBuilding, int& result)
{
     result = result + playerBuilding->getCaptureValue();
     result = result - enemyBuilding->getCaptureValue();
}

void calculateBuildingsDistance(Player* player, Player* enemy, Building* playerBuilding, Building* enemyBuilding, int& result)
{
    for (Unit* unit : player->getUnitList()) {
        if(playerBuilding->getCaptureValue() == playerBuilding->getCapturePoints()
           || !playerBuilding->isCaptured(enemy->getId())){
            result = result - unit->getPosition().distance(enemyBuilding->getPosition());
        }
    }
    
    for (Unit* unit : enemy->getUnitList()) {
        if(enemyBuilding->getCaptureValue() == enemyBuilding->getCapturePoints()
           || !enemyBuilding->isCaptured(player->getId())){
            result = result + unit->getPosition().distance(playerBuilding->getPosition());
        }
    }
}

void calculateUnitsHealth(Player* player, Player* enemy, int& result)
{
    for (Unit* unit : player->getUnitList()) {
        result = result + unit->getHP();
    }
    for (Unit* unit : enemy->getUnitList()) {
        result = result - unit->getHP();
    }
}

int GameState::getStaticEvaluation()
{
    // Positive scores are good for AI
    // Negative scores are good for Human player

    int result = DRAW_VALUE;
    
    int playerId = player->getId();
    int enemyId = enemy->getId();
    Map *map = player->getMap();
    Building* playerBuilding = map->getBuildingByOwnerId(playerId);
    Building* enemyBuilding = map->getBuildingByOwnerId(enemyId);
    
    calculateBuildingsHealth(playerBuilding, enemyBuilding, result);
    calculateBuildingsDistance(player, enemy, playerBuilding, enemyBuilding, result);
    calculateUnitsHealth(player, enemy, result);

    return result;
}

void GameState::processMove(Option *move)
{
    std::cout << "//////////////MOVE FORWARD//////////\n";
    std::cout << "Option executed \n";
    move->execute();
    //TODO Minimax debug : remove
//    renderer->renderClear();
//    scene->render();
//    renderer->renderPresent();
}

void GameState::unprocessMove(Option *move)
{
    std::cout << "Option canceled \n";
    move->cancel();
}
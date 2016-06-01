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

void calculateBuildingsHealth(std::list<Building*> playerBuildings, std::list<Building*> enemyBuildings, int& result)
{
    for (Building* building : playerBuildings) {
           result = result + building->getCaptureValue();
    }
    
    for (Building* building : enemyBuildings) {
        result = result - building->getCaptureValue();
    }
}

void calculateBuildingsDistance(Player* player, Player* enemy, std::list<Building*> playerBuildings, std::list<Building*> enemyBuildings, int& result)
{
    Building* playerHeadquarters = nullptr;
    Building* enemyHeadquarters = nullptr;
    if(playerBuildings.size()>0){
        playerHeadquarters = playerBuildings.back();
    }
    if(enemyBuildings.size()>0){
        enemyHeadquarters = enemyBuildings.back();
    }
    for (Unit* unit : player->getUnitList()) {
        if(enemyHeadquarters != nullptr){
            result = result - unit->getPosition().distance(enemyHeadquarters->getPosition());
        }
    }
    for (Unit* unit : enemy->getUnitList()) {
        if(playerHeadquarters != nullptr){
            result = result + unit->getPosition().distance(playerHeadquarters->getPosition());
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
    Map *map = player->getMap();
    int playerId = player->getId();
    int enemyId = enemy->getId();
    
    int numBuildingsPlayer = map->getNumBuildings(playerId);
    int numBuildingsEnemy = map->getNumBuildings(enemyId);

    std::list<Building*> playerBuildings = map->getBuildingsByOwnerId(playerId);
    std::list<Building*> enemyBuildings = map->getBuildingsByOwnerId(enemyId);
    
    calculateBuildingsHealth(playerBuildings, enemyBuildings, result);
    calculateBuildingsDistance(player, enemy, playerBuildings, enemyBuildings, result);
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
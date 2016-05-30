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
    // Positive scores are good for AI
    // Negative scores are good for Human player
    
    Point pointPlayerBuilding;
    Point pointEnemyBuilding;
    int result = DRAW_VALUE;
    Map *map = player->getMap();
    
    int playerId = player->getId();
    int enemyId = enemy->getId();
    
    Building* playerBuilding = nullptr;
    Building* enemyBuilding = nullptr;
    
    for (Building* building : map->getBuildings()) {
        if(building->getOwnerID()==playerId){
            playerBuilding = building;
        }else if(building->getOwnerID()==enemyId){
            enemyBuilding = building;
        }
    }
    
    pointPlayerBuilding = playerBuilding->getPosition();
    pointEnemyBuilding = enemyBuilding->getPosition();
    
    result = result + playerBuilding->getCaptureValue();
    result = result - enemyBuilding->getCaptureValue();
    
    for (Unit* unit : player->getUnitList()) {
        result = result + unit->getHP();
        if(playerBuilding->getCaptureValue() == playerBuilding->getCapturePoints()){
            result = result - unit->getPosition().distance(pointEnemyBuilding);
        }
    }
    
    for (Unit* unit : enemy->getUnitList()) {
        result = result - unit->getHP();
        if(enemyBuilding->getCaptureValue() == enemyBuilding->getCapturePoints()){
            result = result + unit->getPosition().distance(pointPlayerBuilding);
        }
    }
    
    

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
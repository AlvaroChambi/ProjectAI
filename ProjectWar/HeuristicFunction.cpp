//
//  HeuristicFunction.cpp
//  ProjectWar
//
//  Created by Pablo Luis Gutierrez on 02/06/16.
//  Copyright © 2016 Alvaro Chambi Campos. All rights reserved.
//

#include <stdio.h>
#include "HeuristicFunction.h"

HeuristicFunction::HeuristicFunction(){
    
}

HeuristicFunction::HeuristicFunction(Player* player, Player* enemy)
:player(player),
enemy(enemy){
    
}

HeuristicFunction::~HeuristicFunction() {
    
}

int HeuristicFunction::calculateBuildingsHealth(std::list<Building*> playerBuildings, std::list<Building*> enemyBuildings)
{
    int result = 0;
    for (Building* building : playerBuildings) {
        result = result + building->getCaptureValue();
    }
    
    for (Building* building : enemyBuildings) {
        result = result - building->getCaptureValue();
    }
    return result;
}

//Calculate the distance only to the enemy Headquarters
int HeuristicFunction::calculateBuildingsDistance(Player* player, Player* enemy, std::list<Building*> playerBuildings, std::list<Building*> enemyBuildings)
{
    int result = 0;
    Building* playerHeadquarters = nullptr;
    Building* enemyHeadquarters = nullptr;
    
    //TODO change this to get only the headquarters of each player
    if(!playerBuildings.empty()){
        playerHeadquarters = playerBuildings.back();
    }
    if(!enemyBuildings.empty()){
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
    return result;
}

int HeuristicFunction::calculateUnitsHealth(Player* player, Player* enemy)
{
    int result = 0;
    for (Unit* unit : player->getAliveUnits()) {
        result = result + unit->getHP();
    }
    for (Unit* unit : enemy->getAliveUnits()) {
        result = result - unit->getHP();
    }
    return result;
}

int HeuristicFunction::getStaticEvaluation()
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
    
    result = result + calculateBuildingsHealth(playerBuildings, enemyBuildings);
    result = result + calculateBuildingsDistance(player, enemy, playerBuildings, enemyBuildings);
    result = result + calculateUnitsHealth(player, enemy);
    
    return result;
}
//
//  HeuristicFunction.cpp
//  ProjectWar
//
//  Created by Pablo Luis Gutierrez on 02/06/16.
//  Copyright © 2016 Alvaro Chambi Campos. All rights reserved.
//

#include <stdio.h>
#include "HeuristicFunction.h"

HeuristicFunction::HeuristicFunction() {
    
}

HeuristicFunction::HeuristicFunction( Player* player, Player* enemy )
:player(player), enemy(enemy) {
    
}

HeuristicFunction::~HeuristicFunction() {
    
}

int HeuristicFunction::calculateBuildingsHealth(std::list<Building*> playerBuildings,
                                                std::list<Building*> enemyBuildings) {
    int result = 0;
    for (Building* building : playerBuildings) {
        result = result + building->getCaptureValue();
    }
    
    for (Building* building : enemyBuildings) {
        result = result - building->getCaptureValue();
    }
    return result;
}

int HeuristicFunction::calculateEnemyHeadquarterDistance( Building* playerHeadquarter,
                                                          Building* enemyHeadquarter ) {
    int result = 0;
    //TODO: FIX Headquarter reference
    if(enemyHeadquarter != nullptr && playerHeadquarter != nullptr){
        for (Unit* unit : player->getUnits()) {
            result = result - unit->getPosition().distance(enemyHeadquarter->getPosition());
        }
        for (Unit* unit : enemy->getUnits()) {
            result = result + unit->getPosition().distance(playerHeadquarter->getPosition());
        }
    }
    return result;
}

int HeuristicFunction::calculateUnitsHealth(Player* player, Player* enemy) {
    int result = 0;
    for (Unit* unit : player->getUnits()) {
        result = result + unit->getHP();
    }
    for (Unit* unit : enemy->getUnits()) {
        result = result - unit->getHP();
    }
    return result;
}

int HeuristicFunction::getStaticEvaluation() {
    // Positive scores are good for AI
    // Negative scores are good for Human player
    
    int result = DRAW_VALUE;
    Map *map = player->getMap();
    int playerId = player->getId();
    int enemyId = enemy->getId();
    
    std::list<Building*> playerBuildings = map->getBuildingsByOwnerId(playerId);
    std::list<Building*> enemyBuildings = map->getBuildingsByOwnerId(enemyId);
    
    result = result + calculateBuildingsHealth( playerBuildings, enemyBuildings );
    result = result + calculateEnemyHeadquarterDistance( player->getHeadquarter(),
                                                         enemy->getHeadquarter() );
    result = result + calculateUnitsHealth(player, enemy) * 10;
    
    return result;
}
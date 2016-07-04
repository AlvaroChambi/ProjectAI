//
//  HeuristicFunction.cpp
//  ProjectWar
//
//  Created by Pablo Luis Gutierrez on 02/06/16.
//  Copyright © 2016 Alvaro Chambi Campos. All rights reserved.
//

#include <stdio.h>
#include "HeuristicFunction.h"

HeuristicFunction::HeuristicFunction( const Player& player, const Player& enemy )
:player( player ), enemy( enemy ) {
    
}

int HeuristicFunction::calculateBuildingsHealth(
                                    std::vector<Building*> playerBuildings,
                                    std::vector<Building*> enemyBuildings ) {
    int result = 0;
    for (Building* building : playerBuildings) {
        result = result + building->getCaptureValue();
    }
    
    for (Building* building : enemyBuildings) {
        result = result - building->getCaptureValue();
    }
    return result;
}

int HeuristicFunction::calculateEnemyHeadquarterDistance(
                                            const Building& playerHeadquarter,
                                            const Building& enemyHeadquarter ) {
    int result = 0;
    for ( Unit* unit : player.getUnits() ) {
        result = result -
        unit->getPosition().distance( enemyHeadquarter.getPosition() );
    }
    for ( Unit* unit : enemy.getUnits() ) {
        result = result +
        unit->getPosition().distance( playerHeadquarter.getPosition() );
    }

    return result;
}

int HeuristicFunction::calculateUnitsHealth() {
    int result = 0;
    for (Unit* unit : player.getUnits()) {
        result = result + unit->getHP();
    }
    for (Unit* unit : enemy.getUnits()) {
        result = result - unit->getHP();
    }
    return result;
}

int HeuristicFunction::getStaticEvaluation() {
    // Positive scores are good for AI
    // Negative scores are good for Human player
    
    int result = DRAW_VALUE;
    
    std::vector<Building*> playerBuildings = player.getStructures();
    std::vector<Building*> enemyBuildings = enemy.getStructures();
    
    result = result + calculateBuildingsHealth( playerBuildings, enemyBuildings );
    result = result + calculateEnemyHeadquarterDistance( *player.getHeadquarter(),
                                                         *enemy.getHeadquarter() );
    result = result + calculateUnitsHealth() * 10;
    
    return result;
}
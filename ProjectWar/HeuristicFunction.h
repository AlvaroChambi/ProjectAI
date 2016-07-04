//
//  HeuristicFunction.h
//  ProjectWar
//
//  Created by Pablo Luis Gutierrez on 02/06/16.
//  Copyright © 2016 Alvaro Chambi Campos. All rights reserved.
//

#ifndef HeuristicFunction_h
#define HeuristicFunction_h

#include <stdio.h>
#include "Player.h"
#include "Map.h"

class HeuristicFunction {
public:
    HeuristicFunction();
    HeuristicFunction( const Player& player, const Player& enemy );
    
    static const int DRAW_VALUE = 0;
    
    int calculateBuildingsHealth(
                            std::vector<Building*> playerBuildings,
                            std::vector<Building*> enemyBuildings);
    int calculateEnemyHeadquarterDistance(
                                const Building& playerHeadquarter,
                                const Building& enemyHeadquarter );
    int calculateUnitsHealth();
    int getStaticEvaluation();
private:
    const Player& player;
    const Player& enemy;
    
};
#endif /* HeuristicFunction_h */

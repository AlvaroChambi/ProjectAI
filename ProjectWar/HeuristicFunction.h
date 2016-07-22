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
    static const int DRAW_VALUE = 0;
    static const int WIN_VALUE = 10000;
    static const int LOST_VALUE = -10000;
    static const int NOT_FINISHED = 0;
    
    int calculateBuildingsHealth(
                            const Player& player,
                            const Player& enemy,
                            std::vector<Building*> playerBuildings,
                            std::vector<Building*> enemyBuildings);
    int calculateEnemyHeadquarterDistance(
                                const Player& player,
                                const Player& enemy,
                                const Building& playerHeadquarter,
                                const Building& enemyHeadquarter );
    int calculateUnitsHealth( const Player& player,
                              const Player& enemy );
    int getStaticEvaluation( const Player& player,
                             const Player& enemy );
    
    int getGameOverScore( const Player& player,
                          const Player& enemy );
    
};
#endif /* HeuristicFunction_h */

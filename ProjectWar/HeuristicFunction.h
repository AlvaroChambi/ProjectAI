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
    HeuristicFunction(Player* player, Player* enemy);
    ~HeuristicFunction();
    
    static const int DRAW_VALUE = 0;
    
    int calculateBuildingsHealth(std::list<Building*> playerBuildings, std::list<Building*> enemyBuildings);
    int calculateEnemyHeadquarterDistance(Player* player, Player* enemy, std::list<Building*> playerBuildings, std::list<Building*> enemyBuildings);
    int calculateUnitsHealth(Player* player, Player* enemy);
    int getStaticEvaluation();
private:
    Player* player;
    Player* enemy;
    
};
#endif /* HeuristicFunction_h */

//
//  TacticBuilder.h
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 25/4/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#ifndef __ProjectWar__TacticBuilder__
#define __ProjectWar__TacticBuilder__

#include <stdio.h>
#include "Tactic.h"
#include "Building.h"
#include "GameState.h"

class TacticBuilder
{
public:
    TacticBuilder(GameState& game);
    ~TacticBuilder();
    Tactic* createTactic(TacticType type, Player* player, Player* enemy);;
private:
    void buildTactic(Player* player, Player* enemy, Tactic* tactic);
    void genUnitMovement(Unit* unit, Player* player, Player* enemy, Tactic* tactic);
    Building* getBuilding(Player* player, Unit*, Map* map);
    Unit* getTarget(Unit* unit, Player* enemy);
    GameState& game;
    int count;
};

#endif /* defined(__ProjectWar__TacticBuilder__) */

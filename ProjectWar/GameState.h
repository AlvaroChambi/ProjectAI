//
//  GameState.h
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 25/4/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#ifndef __ProjectWar__GameState__
#define __ProjectWar__GameState__

#include <stdio.h>
#include "Option.h"
#include "Player.h"

#include "Scene.h"
#include "IMap.h"

class GameState {
public:
    static const int WIN_VALUE = 20;
    static const int LOST_VALUE = -10;
    static const int NOT_FINISHED = 0;
    
    GameState( IPlayer* const player, IPlayer* const enemy,
               IMap* map );
    ~GameState();
    
    int getGameOverScore();
    
    std::vector<Option*>* getMovesList( Player* player,
                                        Player* opponent );
    
    IPlayer* const getPlayer();
    IPlayer* const getEnemy();
    
    std::vector<Action*>* filterUnitActions( Unit* unit,
                                             Player* player,
                                             Player* opponent,
                                             int numActions );
    
    std::vector<Action*>* getBestUnitMoves( Building* headquarter,
                                            Unit* unit );
private:
    IPlayer* const enemy;
    IPlayer* const player;
    IMap* map;
};

#endif /* defined(__ProjectWar__GameState__) */

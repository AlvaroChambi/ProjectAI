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
#include "MapContext.h"

class GameState {
public:
    static const int WIN_VALUE = 10000;
    static const int LOST_VALUE = -10000;
    static const int NOT_FINISHED = 0;
    
    GameState( IPlayer* const player, IPlayer* const enemy,
               MapContext* map );
    ~GameState();
    
    std::vector<Option*>& getLegalActions( const Player& player,
                                           const Player& opponent );
    int getStaticEvaluation();
    
    
    std::vector<Option*>* getMovesList( Player* player,
                                        Player* opponent );
    
    void generateTacticSequence(
                        std::vector<std::vector<int>> *sequence,
                        int numElements, std::vector<int> variation,
                        int count );
    std::vector<Option*>& buildMovesList(
                        int units,
                        std::vector<std::vector<Action*>*>& actions );
    
    IPlayer* const getPlayer();
    IPlayer* const getEnemy();
    
    std::vector<Action*>* filterUnitActions( Unit* unit,
                                             Player* player,
                                             Player* opponent,
                                             int numActions );
    
    std::vector<Point>* getBestUnitDestination(
                                        const Building& headquarter,
                                        const Building& ownHeadquarter,
                                        const Unit& unit );
    
    bool isInvalidated( Point position );
    void addToInvalidated( Point position );
private:
    IPlayer* const enemy;
    IPlayer* const player;
    
    MapContext* map;
    std::vector<Point> invalidatedPositions;
};

#endif /* defined(__ProjectWar__GameState__) */

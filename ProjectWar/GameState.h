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

class GameState
{
public:
    //TODO implement copy constructor
    GameState(Player* player, Player* enemy);
    virtual ~GameState();
    
    static const int WIN_VALUE = 20;
    static const int LOST_VALUE = 0;
    static const int DRAW_VALUE = 10;
    
    bool isGameOver();
    int getStaticEvaluation();
    void processMove(Option* move);
    void unprocessMove(Option* move);
    
    Player* enemy;
    Player* player;
private:
protected:
    
};

#endif /* defined(__ProjectWar__GameState__) */

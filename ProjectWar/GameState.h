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

class GameState
{
public:
    //TODO implement copy constructor
    GameState(Player* player, Player* enemy, Scene* scene, Renderer* renderer);
    virtual ~GameState();
    
    static const int WIN_VALUE = 10;
    static const int LOST_VALUE = -10;
    static const int DRAW_VALUE = 0;
    
    bool isGameOver();
    int getStaticEvaluation();
    void processMove(Option* move);
    void unprocessMove(Option* move);
    
    Player* enemy;
    Player* player;
private:
    //TODO Minimax debug : remove
    Scene* scene;
    Renderer* renderer;
    
protected:
    
};

#endif /* defined(__ProjectWar__GameState__) */

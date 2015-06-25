//
//  GameModel.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 11/6/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#include "GameModel.h"
#include <list>
#include "Player.h"
#include "Map.h"

class GameModel
{
public:
    GameModel(std::list<Player*> players, Map* map) : players(players), map(map)
    {
        
    }
    ~GameModel();
    
    std::list<Player*> players;
    Map* map;
};
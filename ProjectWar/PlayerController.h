//
//  PlayerController.h
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 15/3/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#ifndef __ProjectWar__PlayerController__
#define __ProjectWar__PlayerController__

#include <stdio.h>
#include <iostream>
#include "IPlayerEventsListener.h"
#include "Player.h"
#include "Sprite.h"

class PlayerController : public IPlayerEventsListener
{
public:
    PlayerController();
    virtual ~PlayerController();
    void setPlayer(Player* player);
    
    void onMapClicked(const Tile tile);
    void onUnitClicked(const int id);
    
private:
    Player* player;
};

#endif /* defined(__ProjectWar__PlayerController__) */

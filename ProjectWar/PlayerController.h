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
#include "IGameEventsListener.h"
#include "Player.h"

class PlayerController : public IGameEventsListener
{
public:
    PlayerController();
    virtual ~PlayerController();
    void setPlayer(Player* player);
    
    void onTextureClicked(const Texture texture);
    void onSceneClicked(const Point position);
    void onMapClicked(const Tile tile);
private:
    Player* player;
};

#endif /* defined(__ProjectWar__PlayerController__) */

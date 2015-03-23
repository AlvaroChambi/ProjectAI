//
//  ProjectAI.h
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 23/3/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#ifndef __ProjectWar__ProjectAI__
#define __ProjectWar__ProjectAI__

#include <stdio.h>
#include "GameImplementation.h"
#include "Player.h"
#include "PlayerController.h"

class ProjectAI : public GameImplementation
{
public:
    void onSceneClicked(const Point position);
    void onTextureClicked(const Texture texture);
    void onMapClicked(const Tile tile);
    void onSpriteClicked(const int id);
    
    void addPlayer(Player* player);
    void removePlayer(Player* player);
    Player* getPlayer(int position);

private:
    Texture* sprite;
    std::list<Player*> players;
    PlayerController* playerController;
    Player* activePlayer;

};

#endif /* defined(__ProjectWar__ProjectAI__) */

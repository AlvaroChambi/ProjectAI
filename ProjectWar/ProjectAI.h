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
#include "SpriteFactory.h"
#include "Color.h"
#include "Button.h"

class ProjectAI : public GameImplementation
{
public:
    ProjectAI();
    virtual ~ProjectAI();
    void onSceneClicked(const Point position);
    void onTextureClicked(const Texture texture);
    void onMapClicked(const Tile tile);
    void onSpriteClicked(const int id);
    void onUIComponentClicked(UIComponent component);
    
    void onGameStarted(Scene* scene, Renderer* renderer);
    
    void addPlayer(Player* player);
    Player* getPlayer(int position);
    
    Player* nextPlayer();

    //Define this colors as a global static type
    const Color RED = Color(255,0,0);
    const Color GREEN = Color(0,153,0);
    const Color BLUE = Color(0,0,255);
    const Color YELLOW = Color(255,255,0);
    const Color CIAN = Color(0,255,255);
private:
    //TODO Change it for a linked list!
    Player* players[20];
    int numPlayers;
    PlayerController* playerController;
    Player* activePlayer;
    
    int playerTurn;
    int day;
};

#endif /* defined(__ProjectWar__ProjectAI__) */

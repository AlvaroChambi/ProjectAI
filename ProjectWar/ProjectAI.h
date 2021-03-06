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
#include "PlayerController.h"
#include "SpriteFactory.h"
#include "Color.h"
#include "Button.h"
#include "UnitUIView.h"
#include "GameUI.h"

class ProjectAI : public GameImplementation
{
public:
    ProjectAI();
    virtual ~ProjectAI();
    void onSceneClicked(const Point position);
    void onTextureClicked(const Texture* texture);
    void onMapClicked(const Tile tile);
    void onSpriteClicked(const int id);
    void onUIComponentClicked(UIComponent* component);
    
    void onGameStarted(Scene* scene, Renderer* renderer);
    
    void addPlayer(Player* player);
    Player* getPlayer(int position);
    
    Unit* getUnit(int id);
    
    Player* nextPlayer();

    //Define this colors as a global static type
    const Color RED = Color(255,0,0);
    const Color GREEN = Color(0,153,0);
    const Color BLUE = Color(0,0,255);
    const Color YELLOW = Color(255,255,0);
    const Color CIAN = Color(0,255,255);
    //UI button
    static const int END_BUTTON = 1;
    static const int WAIT_BUTTON = 2;
    static const int CANCEL_BUTTON = 3;
    static const int ATTACK_BUTTON = 4;
    static const int CAPTURE_BUTTON = 5;
    
private:
    Input getPlayerEvent(int id);
    
    std::list<Player*> players;
    
    PlayerController* playerController;
    Player* activePlayer;
    
    int playerTurn;
    int day;
    
    UnitUIView* layout;
    GameUI* gameLayout;
    MapContext* mapContext;
};

#endif /* defined(__ProjectWar__ProjectAI__) */

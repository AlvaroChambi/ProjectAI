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
#include "UnitUIView.h"
#include "MenuScene.h"
#include "GameScene.h"
#include "Text.h"

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
    
    void onGameStarted(SceneManager* sceneManager, Renderer* renderer);
    
    void addPlayer(Player* player);
    Player* getPlayer(int position);
    
    Unit* getUnit(int id);
    
    Player* nextPlayer();

    //UI button
    static const int END_BUTTON = 1;
    static const int WAIT_BUTTON = 2;
    static const int CANCEL_BUTTON = 3;
    static const int ATTACK_BUTTON = 4;
    static const int CAPTURE_BUTTON = 5;
    
    SpriteFactory* spriteFactory;
    Renderer* renderer;
    SceneManager* sceneManager;
    
    Player* activePlayer;
    
    Text* foundsText;
    Text* playerText;
private:
    Input getPlayerEvent(int id);
    Scene* gameScene(Scene* scene, Renderer* renderer);
    Player* prepareOpponent(SpriteFactory* spriteFactory, Scene* scene, Renderer* renderer, Map* map);
    
    std::list<Player*> players;
    
    Map* map;
    
    PlayerController* playerController;
    
    int playerTurn;
    int day;
    
    UnitUIView* layout;
    int founds;
};

#endif /* defined(__ProjectWar__ProjectAI__) */

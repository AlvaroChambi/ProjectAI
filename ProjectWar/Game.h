//
//  Game.h
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 10/3/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#ifndef __ProjectWar__Game__
#define __ProjectWar__Game__

#include <stdio.h>
#include <list>

#include "SDLRenderer.h"
#include "Scene.h"
#include "SDLInputHandler.h"
#include "Player.h"
#include "PlayerView.h"
#include "PlayerController.h"
#include "UnitView.h"
#include "SpriteFactory.h"

class Game : IGameEventsListener
{
public:
    Game();
    virtual ~Game();
    virtual void onInit();
    virtual void onProcessInput();
    virtual void onUpdate();
    virtual void onRender();
    virtual void onFinish();
    void onSceneClicked(const Point position);
    void onTextureClicked(const Texture texture);
    void onMapClicked(const Tile tile);
    void onSpriteClicked(const int id);
    bool isRunning();
    void addPlayer(Player* player);
    void removePlayer(Player* player);
    Player* getPlayer(int position);
    
    //Define this colors as a global static type
    const Color RED = Color(255,0,0);
    const Color GREEN = Color(0,153,0);
    const Color BLUE = Color(0,0,255);
protected:
private:
    bool gameRunning;
    SDLRenderer* renderer;
    SDLInputHandler* inputHandler;
    Scene* scene;
    
    //Game specific info
    Texture* sprite;
    std::list<Player*> players;
    PlayerController* playerController;
    Player* activePlayer;
};

#endif /* defined(__ProjectWar__Game__) */

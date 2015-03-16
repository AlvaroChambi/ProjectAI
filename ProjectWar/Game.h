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
    bool isRunning();
    void addPlayer(Player* player);
    void removePlayer(Player* player);
    Player* getPlayer(int position);
    
    //Define this colors as an static type
    const Color RED = Color(255,0,0);
    const Color GREEN = Color(0,153,0);
protected:
private:
    bool gameRunning;
    SDLRenderer* renderer;
    SDLInputHandler* inputHandler;
    Scene* scene;
    Texture* sprite;
    std::list<Player*> players;
    PlayerController* playerController;
};

#endif /* defined(__ProjectWar__Game__) */

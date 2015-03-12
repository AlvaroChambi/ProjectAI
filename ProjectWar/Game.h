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
#include "SDLRenderer.h"
#include "Scene.h"
#include "SDLInputHandler.h"

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
    bool isRunning();
protected:
private:
    bool gameRunning;
    SDLRenderer* renderer;
    SDLInputHandler* inputHandler;
    Scene* scene;
    Texture* sprite;
};

#endif /* defined(__ProjectWar__Game__) */

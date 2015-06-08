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
#include "SceneManager.h"
#include "SDLInputHandler.h"
#include "GameImplementation.h"
#include "ProjectAI.h"

class Game 
{
public:
    Game();
    virtual ~Game();
    virtual void onInit();
    virtual void onProcessInput();
    virtual void onUpdate();
    virtual void onRender();
    virtual void onFinish();
    bool isRunning();
    
protected:
private:
    bool gameRunning;
    SDLRenderer* renderer;
    SDLInputHandler* inputHandler;
    SceneManager* manager;
    GameImplementation* gameImplementation;    
};

#endif /* defined(__ProjectWar__Game__) */

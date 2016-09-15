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
#include "GameImplementation.h"
#include "ProjectAI.h"
#include "Configuration.h"

class Game 
{
public:
	static Configuration config;

	Game();
    virtual ~Game();
    virtual void onInit();
    virtual void onProcessInput();
    virtual void onUpdate();
    virtual void onRender();
    virtual void onFinish();
    bool isRunning();

private:
    bool gameRunning;
    SDLRenderer* renderer;
    SDLInputHandler* inputHandler;
    Scene* scene;
    GameImplementation* gameImplementation;    
};

#endif /* defined(__ProjectWar__Game__) */

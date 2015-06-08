//
//  GameImplementation.h
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 23/3/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#ifndef ProjectWar_GameImplementation_h
#define ProjectWar_GameImplementation_h

#include "IGameEventsListener.h"
#include "SceneManager.h"

class GameImplementation : public IGameEventsListener
{
    
public:
    virtual void onGameStarted( SceneManager* sceneManager, Renderer* renderer ) = 0;
};

#endif

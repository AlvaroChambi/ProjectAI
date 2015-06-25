//
//  GameScene.h
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 11/6/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#ifndef __ProjectWar__GameScene__
#define __ProjectWar__GameScene__

#include <stdio.h>
#include "Scene.h"

class GameScene : public Scene
{
public:
    GameScene(Renderer* renderer);
    ~GameScene();
    
    void onSceneStarted();
    void onScenePaused();
    void onSceneFinished();
    
};

#endif /* defined(__ProjectWar__GameScene__) */

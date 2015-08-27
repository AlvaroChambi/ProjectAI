//
//  MapSelectScene.h
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 14/8/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#ifndef __ProjectWar__MapSelectScene__
#define __ProjectWar__MapSelectScene__

#include <stdio.h>
#include "Scene.h"

class MapSelectScene : public Scene
{
public:
    MapSelectScene(Renderer* renderer, SceneManager* sceneManager);
    ~MapSelectScene();
    
    void onSceneStarted();
    void onScenePaused();
    void onSceneFinished();
};

#endif /* defined(__ProjectWar__MapSelectScene__) */

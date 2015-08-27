//
//  MenuScene.h
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 11/6/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#ifndef __ProjectWar__MenuScene__
#define __ProjectWar__MenuScene__

#include <stdio.h>
#include "Scene.h"

class MenuScene : public Scene
{
public:
    MenuScene(Renderer* renderer, SceneManager* manager);
    ~MenuScene();
    
    void onSceneStarted();
    void onScenePaused();
    void onSceneFinished();
};

#endif /* defined(__ProjectWar__MenuScene__) */

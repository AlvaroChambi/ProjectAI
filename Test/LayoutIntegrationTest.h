//
//  LayoutIntegrationTest.h
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 8/9/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#ifndef __ProjectWar__LayoutIntegrationTest__
#define __ProjectWar__LayoutIntegrationTest__

#include <stdio.h>
#include "Scene.h"

class LayoutIntegrationTest : public Scene
{
public:
    LayoutIntegrationTest(Renderer* renderer, SceneManager* sceneManager);
    ~LayoutIntegrationTest();
    
    void onSceneStarted();
    void onScenePaused();
    void onSceneFinished();
};

#endif /* defined(__ProjectWar__LayoutIntegrationTest__) */

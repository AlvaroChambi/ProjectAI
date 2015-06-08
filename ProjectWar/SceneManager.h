//
//  SceneManager.h
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 4/6/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#ifndef __ProjectWar__SceneManager__
#define __ProjectWar__SceneManager__

#include <iostream>
#include <map>
#include "Scene.h"

class SceneManager
{
public:
    SceneManager();
    ~SceneManager();
    
    void registerScene(Scene* scene, std::string tag);
    //TODO actual scene not needed...
    void changeScene(std::string actualScene, std::string newScene);
    void changeScene(std::string newScene, int extras);
    void setActualScene(Scene* scene, std::string tag);
    
    Scene* getActualScene();
    Scene* getScene(std::string tag);
private:
    std::map<std::string, Scene*> scenes;
    Scene* actualScene;
};

#endif /* defined(__ProjectWar__SceneManager__) */

//
//  SceneManager.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 4/6/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#include "SceneManager.h"

SceneManager::SceneManager()
{

}

SceneManager::~SceneManager()
{
    
}

void SceneManager::setActualScene(Scene* newScene, std::string tag)
{
    this->registerScene(newScene, tag);
    this->actualScene = newScene;
    //TODO maybe make this call assynchronous
    this->actualScene->onSceneStarted();
}

void SceneManager::changeScene(std::string actualScene, std::string newScene)
{
    this->actualScene->onScenePaused();
    this->actualScene = scenes[newScene];
    this->actualScene->onSceneStarted();
}

void SceneManager::changeScene(std::string newScene, int extras)
{
    this->actualScene->onScenePaused();
    Scene* scene = scenes[newScene];
    scene->setExtras(extras);
    this->actualScene = scene;
    this->actualScene->onSceneStarted();
}

void SceneManager::registerScene(Scene *scene, std::string tag)
{
    scenes[tag] = scene;
}

Scene* SceneManager::getScene(std::string tag)
{
    return scenes[tag];
}

Scene* SceneManager::getActualScene()
{
    return actualScene;
}
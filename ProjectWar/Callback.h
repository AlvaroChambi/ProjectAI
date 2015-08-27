//
//  Callback.h
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 11/6/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#ifndef ProjectWar_Callback_h
#define ProjectWar_Callback_h
#include "Message.h"
class SceneManager;
class ProjectAI;

class Callback
{
public:
    virtual void function(Message* message) = 0;
};

class ShowPopUpCallback : public Callback
{
public:
    SceneManager* sceneManager;
    ShowPopUpCallback(SceneManager* sceneManager) : sceneManager(sceneManager)
    {}
    void function(Message* message);
};

class HidePopUpCallback : public Callback
{
public:
    SceneManager* sceneManager;
    HidePopUpCallback(SceneManager* sceneManager) : sceneManager(sceneManager)
    {}
    void function(Message* message);
};

class CreateUnitCallback : public Callback
{
public:
    ProjectAI* game;
    CreateUnitCallback(ProjectAI* game) : game(game)
    {}
    void function(Message* message);
};

class UpdateUICallback : public Callback
{
public:
    ProjectAI* game;
    UpdateUICallback(ProjectAI* game) : game(game)
    {}
    void function(Message* message);
};

class CreateBuildingCallback : public Callback
{
public:
    ProjectAI* game;
    CreateBuildingCallback(ProjectAI* game) : game(game)
    {
        
    }
    void function(Message* message);
};

#endif

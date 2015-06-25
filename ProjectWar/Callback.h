//
//  Callback.h
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 11/6/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#ifndef ProjectWar_Callback_h
#define ProjectWar_Callback_h
class SceneManager;

class Callback
{
public:
    virtual void function() = 0;
};

class ShowPopUpCallback : public Callback
{
public:
    SceneManager* sceneManager;
    ShowPopUpCallback(SceneManager* sceneManager) : sceneManager(sceneManager)
    {}
    void function();
};

class HidePopUpCallback : public Callback
{
public:
    SceneManager* sceneManager;
    HidePopUpCallback(SceneManager* sceneManager) : sceneManager(sceneManager)
    {}
    void function();
};

#endif

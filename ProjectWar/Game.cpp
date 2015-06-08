//
//  Game.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 10/3/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#include "Game.h"


Game::Game()
{
    gameRunning = true;
}

Game::~Game()
{
    //dtor
}

void Game::onInit()
{
    renderer = new SDLRenderer;
    manager = new SceneManager();
    inputHandler = new SDLInputHandler();
    renderer->init();
    
    gameImplementation = new ProjectAI;
    gameImplementation->onGameStarted(manager, renderer);
}

void Game::onProcessInput()
{
    Event* event = inputHandler->poolEvent();
    Scene* scene = manager->getActualScene();
    scene->handleEvent(*event);
    switch (event->type) {
        case ON_WINDOW_CLOSED:
            this->gameRunning = false;
            break;
        default:
            break;
    }
}

//TODO use delta time and call entities update time method to handle animations
void Game::onUpdate()
{
    Scene* scene = manager->getActualScene();
    scene->update();
}

void Game::onRender()
{
    renderer->renderClear();
    Scene* scene = manager->getActualScene();
    scene->render();
    renderer->renderPresent();
}

void Game::onFinish()
{
    
}

bool Game::isRunning()
{
    return gameRunning;
}

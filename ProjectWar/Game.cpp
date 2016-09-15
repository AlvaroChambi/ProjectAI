//
//  Game.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 10/3/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#include "Game.h"

Configuration Game::config;

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
	config.load("config.txt");

    renderer = new SDLRenderer;
    scene = new Scene(renderer);
    inputHandler = new SDLInputHandler();
    renderer->init();
    
    gameImplementation = new ProjectAI;
    gameImplementation->onGameStarted(scene, renderer);
}

void Game::onProcessInput()
{
    Event* event = inputHandler->poolEvent();
    scene->handleEvent(*event);
    switch (event->type) {
        case ON_WINDOW_CLOSED:
            this->gameRunning = false;
            break;
        default:
            break;
    }
}

//use detal time and call entities update time method to handle animations
void Game::onUpdate()
{
    this->scene->update();
}

void Game::onRender()
{
    renderer->renderClear();
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

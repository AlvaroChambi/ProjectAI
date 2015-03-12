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
    renderer = new SDLRenderer;
    gameRunning = true;
    scene = new Scene(renderer);
    inputHandler = new SDLInputHandler();
}

Game::~Game()
{
    //dtor
}

bool Game::isRunning()
{
    return gameRunning;
}

void Game::onInit()
{
    renderer->init();
    sprite = renderer->loadTexture("resource");
    scene->attachTexture(sprite);
    scene->registerListener(this);
}

void Game::onProcessInput()
{
    Event* event = inputHandler->poolEvent();
    scene->handleEvent(*event);
    switch (event->type) {
        case ON_WINDOW_CLOSED:
            this->gameRunning = false;
            break;
        case ON_MOUSE_DOWN_EVENT:
            sprite->setPosition(event->x, event->y);
            break;
        default:
            break;
    }
}

void Game::onUpdate()
{

}

void Game::onRender()
{
    renderer->renderClear();
    scene->render();
    renderer->renderPresent();
}

void Game::onSceneClicked(const Point position)
{
    std::cout << "scene clicked\n";
}

void Game::onTextureClicked(const Texture texture)
{
    std::cout << "texture clicked\n";
}

void Game::onFinish()
{

}

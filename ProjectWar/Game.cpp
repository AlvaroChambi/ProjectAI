//
//  Game.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 10/3/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#include "Game.h"
#include "LinkedList.h"

Game::Game()
{
    renderer = new SDLRenderer;
    gameRunning = true;
    scene = new Scene(renderer);
    inputHandler = new SDLInputHandler();
    playerController = new PlayerController;
}

Game::~Game()
{
    //dtor
}

void Game::onSceneClicked(const Point position)
{
    std::cout << "scene clicked: " << position.x << "  " << position.y << "\n";
}

void Game::onTextureClicked(const Texture texture)
{
    std::cout << "texture clicked\n";
}

void Game::onMapClicked(const Tile tile)
{
    //std::cout << "Game\n";
    //std::cout << "map clicked: " << tile.position.x << " " << tile.position.y << "\n";
    playerController->onMapClicked(tile);
}

void Game::onInit()
{
    renderer->init();
    //TODO Load map data model and view resources
    Map* map = new Map();
    map->loadMap(renderer, 40, 40);
    //TODO Load player data model, view and create new controller
    Player* player = new Player();
    PlayerView* playerView = new PlayerView();
    playerView->setModel(player);
    playerController->setPlayer(player);
    Texture* texture = renderer->loadShape(RECTANGLE, RED, 30, 30);
    Texture* sprite = renderer->loadTexture("test.bmp");
    playerView->setTexture(texture);
    texture->setPosition(map->getAbsolutePosition(8,8));
    sprite->setPosition(map->getAbsolutePosition(2, 2));
    //TODO For each player load unit and buildings data model and view resources
    
    
    texture->setZ_order(20);
    
    sprite->setZ_order(15);
    LinkedList lista;
    lista.Insertar(texture);
    lista.Insertar(sprite);
    lista.MostrarLista();
    
    
    //TODO register game and player controller as an scene events listener
    
    scene->attachMap(map);
    scene->attachTexture(texture);
    scene->attachTexture(sprite);
    //scene->attachTexture(sprite);
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

void Game::onFinish()
{
    
}

bool Game::isRunning()
{
    return gameRunning;
}

void Game::addPlayer(Player* player)
{
    players.push_front(player);
}

void Game::removePlayer(Player *player)
{
    players.remove(player);
}

Player* Game::getPlayer(int position)
{
    //TODO search in the list for the element of the given position
    return nullptr;
}





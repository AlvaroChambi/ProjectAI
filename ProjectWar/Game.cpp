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
    //Just one instance of the player controller, the player reference will be update according to the player turn
    playerController = new PlayerController;
}

Game::~Game()
{
    //dtor
}

void Game::onSceneClicked(const Point position)
{
    //std::cout << "scene clicked: " << position.x << "  " << position.y << "\n";
}

void Game::onTextureClicked(const Texture texture)
{
    //std::cout << "texture clicked\n";
}

void Game::onMapClicked(const Tile tile)
{
    //std::cout << "Game\n";
    //std::cout << "map clicked: " << tile.position.x << " " << tile.position.y << "\n";
    playerController->onMapClicked(tile);
}

//TODO Just pass the id of the sprite as parameter
void Game::onSpriteClicked(const int id)
{
    //std::cout << "sprite clicked " << id << "\n";
    //TODO Check if the sprite clicked is a resource of the active player(unit or building)
    playerController->onUnitClicked(id);
}

void Game::onInit()
{
    renderer->init();
    //TODO Load map data model and view resources
    Map* map = new Map();
    map->loadMap(renderer, 40, 40);
    
    SpriteFactory* spriteFactory = new SpriteFactory;
    
    //TODO Load player data model, view and create new controller
    Player* player = new Player();
    Sprite* playerSprite = spriteFactory->createSprite(PLAYER);
    playerSprite->setModel(player);
    playerController->setPlayer(player);
    Texture* texture = renderer->loadShape(RECTANGLE, RED, 30, 30);
    playerSprite->setTexture(texture);
    texture->setPosition(map->getAbsolutePosition(8,8));
    
    //TODO For each player load unit and buildings data model and view resources
    Unit* unit = new Unit();
    unit->setResource("rider.bmp");
    Sprite* unitSprite = spriteFactory->createSprite(UNIT);
    unitSprite->setModel(unit);
    Texture* unitTexture = renderer->loadShape(RECTANGLE, BLUE, 20, 20);
    unitSprite->setTexture(unitTexture);
    
    player->addUnit(unit);
    
    //TODO register game and player controller as an scene events listener
    scene->attachMap(map);
    scene->attachSprite(playerSprite);
    scene->attachSprite(unitSprite);
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





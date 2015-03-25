//
//  ProjectAI.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 23/3/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#include "ProjectAI.h"

ProjectAI::ProjectAI() : numPlayers(0), activePlayer(nullptr), day(0), playerTurn(0)
{
    //Just one instance of the player controller, the player reference will be update according to the player turn
    playerController = new PlayerController;
}

ProjectAI::~ProjectAI()
{

}

void ProjectAI::onSceneClicked(const Point position)
{

}

void ProjectAI::onMapClicked(const Tile tile)
{
    playerController->onMapClicked(tile);
}

void ProjectAI::onSpriteClicked(const int id)
{
    //At this point we must check what kind of sprite triggered the event so we can filter it
    //(unitClicked, oppositeUnitClicked, building clicked, etc...)
    //playerController->onUnitClicked(id);
    switch (this->getPlayerEvent(id)) {
        case UNIT_CLICKED:
            playerController->onUnitClicked(id);
            break;
        case ENEMY_UNIT_CLICKED:
            playerController->onEnemyUnitClicked(id);
            break;
        default:
            break;
    }
}

Input ProjectAI::getPlayerEvent(int id)
{
    Input result = ENEMY_UNIT_CLICKED;
    for (int i = 0; i < numPlayers; i++) {
        if (activePlayer->hasUnit(id)) {
            result = UNIT_CLICKED;
        }
    }
    return result;
}

void ProjectAI::onTextureClicked(const Texture texture)
{

}

void ProjectAI::onUIComponentClicked(UIComponent component)
{
    std::cout << "ui component clicked";
    //Pass the next player the turn
    activePlayer = this->nextPlayer();
}

void ProjectAI::onGameStarted(Scene *scene, Renderer* renderer)
{
    //Set scene ui
    Layout* layout = new Layout();
    Button* button = new Button();
    button->setParams(Params(60,40,CENTER));
    layout->setParams(Params(FILL,100,DOWN));
    scene->setUIHUD(layout);
    layout->addComponent(button);
    button->setTexture(renderer->loadShape(RECTANGLE, BLUE, 60, 40));
    
    //Load map data model and view resources
    Map* map = new Map();
    map->loadMap(renderer, 40, 40);
    
    SpriteFactory* spriteFactory = new SpriteFactory;
    
    //Load player data model, view and create new controller
    Player* player = new Player();
    Sprite* playerSprite = spriteFactory->createSprite(PLAYER);
    playerSprite->setModel(player);
    Texture* texture = renderer->loadShape(RECTANGLE, RED, 40, 40);
    playerSprite->setTexture(texture);
    texture->setPosition(map->getAbsolutePosition(8,8));
    player->setMap(map);
    
    Player* player2 = new Player;
    Sprite* playerSprite2 = spriteFactory->createSprite(PLAYER);
    playerSprite2->setModel(player2);
    Texture* texture2 = renderer->loadShape(RECTANGLE, CIAN, 40, 40);
    texture2->setVisible(false);
    playerSprite2->setTexture(texture2);
    texture2->setPosition(map->getAbsolutePosition(3,8));
    player2->setMap(map);
    
    this->addPlayer(player);
    this->addPlayer(player2);
    //For each player load unit and buildings data model and view resources
    Unit* unit = new Unit();
    unit->setResource("animate.bmp");
    Sprite* unitSprite = spriteFactory->createSprite(UNIT);
    unit->setMovement(3);
    unitSprite->setModel(unit);
    Texture* unitTexture = renderer->loadSprite(unit->getResource(), 128, 82);
    unitSprite->setTexture(unitTexture);
    //resize to fit in a map tile
    unitSprite->resize(40, 40);
    unit->setPosition(map->getTile(4, 4));
    player->addUnit(unit);
    
    Unit* unit2 = new Unit();
    unit2->setResource("link.bmp");
    Sprite* unit2Sprite = spriteFactory->createSprite(UNIT);
    unit2->setMovement(3);
    unit2Sprite->setModel(unit2);
    Texture* unit2Texture = renderer->loadSprite(unit2->getResource(), 90, 90);
    unit2Sprite->setTexture(unit2Texture);
    unit2Sprite->resize(40, 40);
    unit2->setPosition(map->getTile(10, 10));
    player2->addUnit(unit2);
    
    //register game and player controller as an scene events listener
    scene->attachMap(map);
    scene->attachSprite(playerSprite2);
    scene->attachSprite(unit2Sprite);
    scene->attachSprite(playerSprite);
    scene->attachSprite(unitSprite);
    
    scene->registerListener(this);
    
    //Set the first active player and starts the game
    nextPlayer();

}

Player* ProjectAI::nextPlayer()
{
    Player* result;
    //Set the actual active player as non active
    if(activePlayer != nullptr){
        activePlayer->setActive(false);
    }
    if(playerTurn > numPlayers){
        playerTurn = 0;
        day++;
        result = players[playerTurn];
    }else{
        result = players[playerTurn];
        playerTurn++;
    }
    //Update active player and the player controller
    activePlayer = result;
    activePlayer->setActive(true);
    playerController->setPlayer(activePlayer);
    return result;
}

void ProjectAI::addPlayer(Player *player)
{
    players[numPlayers] = player;
    numPlayers++;
}

Player* ProjectAI::getPlayer(int position)
{
    return players[position];
}
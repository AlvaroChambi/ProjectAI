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
    playerController->onUnitClicked(id);
}

void ProjectAI::onTextureClicked(const Texture texture)
{

}

void ProjectAI::onUIComponentClicked(UIComponent component)
{
    std::cout << "ui component clicked";
    //Pass the next player the turn
    activePlayer = this->getNextPlayer();
    playerController->setPlayer(activePlayer);
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
    playerController->setPlayer(player);
    Texture* texture = renderer->loadShape(RECTANGLE, RED, 40, 40);
    playerSprite->setTexture(texture);
    texture->setPosition(map->getAbsolutePosition(8,8));
    player->setMap(map);
    
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
    
    //register game and player controller as an scene events listener
    scene->attachMap(map);
    scene->attachSprite(playerSprite);
    scene->attachSprite(unitSprite);
    
    scene->registerListener(this);

}

Player* ProjectAI::getNextPlayer()
{
    Player* result;
    if(playerTurn > numPlayers){
        playerTurn = 0;
        day++;
        result = players[playerTurn];
    }else{
        result = players[playerTurn];
        playerTurn++;
    }
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
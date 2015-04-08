//
//  ProjectAI.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 23/3/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#include "ProjectAI.h"
#include "UnitUIView.h"

ProjectAI::ProjectAI() : activePlayer(nullptr), day(0), playerTurn(0)
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
        {
            Unit* unit = activePlayer->getSelectedUnit();
            //Updating unit ui reference to the new selected unit
            if(unit == nullptr || unit->getId() != id){
                layout->setModel(activePlayer->getUnit(id));
            }
            playerController->onUnitClicked(id);
        }
            break;
        case ENEMY_UNIT_CLICKED:
            playerController->onEnemyUnitClicked(id);
            break;
        default:
            break;
    }
}

void ProjectAI::onTextureClicked(const Texture texture)
{
    //TODO implement
}

void ProjectAI::onUIComponentClicked(UIComponent component)
{
    switch (component.getID()) {
        case END_BUTTON:
            //Pass the next player the turn
            activePlayer = this->nextPlayer();
            break;
        default:
            playerController->onUIEventReceived(component.getID());
            break;
    }
}

void ProjectAI::onGameStarted(Scene *scene, Renderer* renderer)
{
    
    //Set scene ui
    layout = new UnitUIView();
    Button* button = new Button(END_BUTTON);
    button->setParams(Params(60,40,CENTER));
    layout->setParams(Params(FILL,100,DOWN));
    scene->setUIHUD(layout);
    layout->addComponent(button);
    button->setImageResource("end_button.bmp");
    
    //Load map data model and view resources
    Map* map = new Map();
    map->loadMap(renderer, 40, 40);
    
    SpriteFactory* spriteFactory = new SpriteFactory;
    
    //Load player data model, view
    Player* player = new Player(1);
    Sprite* playerSprite = spriteFactory->createSprite(PLAYER);
    playerSprite->setModel(player);
    Texture* texture = renderer->loadShape(RECTANGLE, RED, 40, 40);
    playerSprite->setTexture(texture);
    texture->setPosition(map->getAbsolutePosition(8,8));
    player->setMap(map);
    
    Player* player2 = new Player(2);
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
    
    /////////  PLAYER 1 UNITS //////////
    Unit* unit = new Unit();
    unit->setResource("animate.bmp");
    Sprite* unitSprite = spriteFactory->createSprite(UNIT);
    unit->setMovement(4);
    unit->setAttackRange(1);
    unitSprite->setModel(unit);
    Texture* unitTexture = renderer->loadSprite(unit->getResource(), 128, 82);
    unitSprite->setTexture(unitTexture);
    //resize to fit in a map tile
    unitSprite->resize(40, 40);
    unit->setPosition(map->getTile(4, 4));
    player->addUnit(unit);
    
    Unit* unit3 = new Unit();
    unit3->setResource("animate.bmp");
    Sprite* unitSprite3 = spriteFactory->createSprite(UNIT);
    unit3->setMovement(4);
    unit3->setAttackRange(1);
    unitSprite3->setModel(unit3);
    Texture* unitTexture3 = renderer->loadSprite(unit3->getResource(), 128, 82);
    unitSprite3->setTexture(unitTexture3);
    //resize to fit in a map tile
    unitSprite3->resize(40, 40);
    unit3->setPosition(map->getTile(8, 9));
    player->addUnit(unit3);
    
    Unit* unit4 = new Unit();
    unit4->setResource("animate.bmp");
    Sprite* unitSprite4 = spriteFactory->createSprite(UNIT);
    unit4->setMovement(4);
    unit4->setAttackRange(1);
    unitSprite4->setModel(unit4);
    Texture* unitTexture4 = renderer->loadSprite(unit3->getResource(), 128, 82);
    unitSprite4->setTexture(unitTexture4);
    //resize to fit in a map tile
    unitSprite4->resize(40, 40);
    unit4->setPosition(map->getTile(4, 9));
    player->addUnit(unit4);
    
    ///////////  PLAYER 2 UNITS ///////////
    Unit* unit2 = new Unit();
    unit2->setResource("link.bmp");
    Sprite* unit2Sprite = spriteFactory->createSprite(UNIT);
    unit2->setMovement(3);
    unit2->setAttackRange(1);
    unit2Sprite->setModel(unit2);
    Texture* unit2Texture = renderer->loadSprite(unit2->getResource(), 90, 90);
    unit2Sprite->setTexture(unit2Texture);
    unit2Sprite->resize(40, 40);
    unit2->setPosition(map->getTile(4, 3));
    player2->addUnit(unit2);
    
    Unit* unit5 = new Unit();
    unit5->setResource("link.bmp");
    Sprite* unitSprite5 = spriteFactory->createSprite(UNIT);
    unit5->setMovement(3);
    unit5->setAttackRange(1);
    unitSprite5->setModel(unit5);
    Texture* unitTexture5 = renderer->loadSprite(unit2->getResource(), 90, 90);
    unitSprite5->setTexture(unitTexture5);
    unitSprite5->resize(40, 40);
    unit5->setPosition(map->getTile(6, 6));
    player2->addUnit(unit5);
    
    //When all the players resources has been setted, load the strategic info map
    map->loadInfoMap(players);
    
    //register game and player controller as an scene events listener
    scene->attachMap(map);
    scene->attachSprite(playerSprite2);
    scene->attachSprite(playerSprite);
    
    scene->attachSprite(unit2Sprite);
    scene->attachSprite(unitSprite3);
    scene->attachSprite(unitSprite4);
    scene->attachSprite(unitSprite5);

    scene->attachSprite(unitSprite);
    
    scene->registerListener(this);
    
    //Set the first active player and starts the game
    nextPlayer();
    
}

//TODO Check this method, returning corrupted player instance sometimes...
Player* ProjectAI::nextPlayer()
{
    Player* result;
    //Set the actual active player as non active
    if(activePlayer != nullptr){
        activePlayer->setActive(false);
    }
    if(playerTurn >= players.getSize()){
        playerTurn = 0;
        day++;
        result = players.getElement(playerTurn);
        playerTurn++;
    }else{
        result = players.getElement(playerTurn);
        playerTurn++;
    }
    //Update active player and the player controller
    activePlayer = result;
    activePlayer->setActive(true);
    playerController->setPlayer(activePlayer);
    return result;
}

//Given an sprite id return an event according to the type of sprite clicked
Input ProjectAI::getPlayerEvent(int id)
{
    Input result = ENEMY_UNIT_CLICKED;
    for (int i = 0; i < players.getSize(); i++) {
        if (activePlayer->hasUnit(id)) {
            result = UNIT_CLICKED;
        }
    }
    return result;
}

void ProjectAI::addPlayer(Player *player)
{
    players.add(player);
}

Player* ProjectAI::getPlayer(int position)
{
    return players.getElement(position);
}
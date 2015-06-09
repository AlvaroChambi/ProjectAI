//
//  ProjectAI.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 23/3/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#include "ProjectAI.h"
#include "UnitUIView.h"
#include "PlayerAI.h"
#include "UnitFactory.h"
#include "VerticalLayout.h"

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
            playerController->onEnemyUnitClicked(getUnit(id));
            break;
        default:
            break;
    }
}

Unit* ProjectAI::getUnit(int id)
{
    Unit* unit = nullptr;
    for (Player* player : players) {
        unit = player->getUnit(id);
        if (unit != nullptr) {
            //Change the way to stop when we get a match...
            return unit;
        }
        
    }
    return unit;
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
            if (activePlayer->getType() == AI_PLAYER) {
                PlayerAI* playerAI = (PlayerAI*)activePlayer;
                playerAI->play();
                this->onUIComponentClicked(*new Button(END_BUTTON));
            }
            break;
            //TODO DEBUG!
        case 10:
            std::cout << "player_player\n";
            //TODO inherit from scene and make a callback for a scene created, started, destroyed...
            sceneManager->changeScene("game_scene", 0);
            gameScene(sceneManager->getScene("game_scene"), renderer);
            //Set the first active player and starts the game
            nextPlayer();
            break;
        case 11:
            std::cout << "player_ai\n";
            sceneManager->changeScene("game_scene", 1);
            gameScene(sceneManager->getScene("game_scene"), renderer);
            //Set the first active player and starts the game
            nextPlayer();
            break;
        default:
            playerController->onUIEventReceived(component.getID());
            break;
    }
}

Scene* ProjectAI::mainMenuScene( SceneManager* sceneManager, Renderer* renderer )
{
    Scene* menuScene = new Scene(renderer);
    VerticalLayout* menuLayout = new VerticalLayout;
    //TODO Change the way to set the ui components id
    Button* menuButton = new Button(10);
    Button* menuButton2 = new Button(11);
    menuButton->setParams(Params(256,128,CENTER));
    menuButton2->setParams(Params(256,128,CENTER));
    //TODO Animate on click
    menuButton->setImageResource("player_player_button.png");
    menuButton2->setImageResource("player_ai_button.png");
    
    menuScene->setUIHUD(menuLayout);
    menuLayout->addComponent(menuButton);
    menuLayout->addComponent(menuButton2);
    
    menuScene->registerListener(this);
    return menuScene;
}

Scene* ProjectAI::gameScene(Scene* scene, Renderer* renderer)
{
    //Set scene ui
    layout = new UnitUIView();
    gameLayout = new GameUI();
    gameLayout->setParams(Params(FILL, 20, DOWN));
    gameLayout->setBackground(renderer->loadShape(RECTANGLE, Color(255,255,255), 256, 256));
    Button* button = new Button(END_BUTTON);
    button->setParams(Params(60,40,CENTER));
    layout->setParams(Params(FILL,100,DOWN));
    scene->setUIHUD(layout);
    layout->addComponent(button);
    layout->addComponent(gameLayout);
    button->setImageResource("end_button.bmp");
    
    //Load map data model and view resources
    Map* map = new Map();
    map->loadMap(renderer, 40, 40);
    
    SpriteFactory* spriteFactory = new SpriteFactory;
    
    //TODO fix error assigning id to the sprites and models
    //Load player data model, view
    Player* player = new Player();
    Sprite* playerSprite = spriteFactory->createSprite(PLAYER);
    playerSprite->setModel(player);
    Texture* texture = renderer->loadTexture("target_tile_white.png");
    playerSprite->setTexture(texture);
    playerSprite->resize(40, 40);
    texture->setPosition(map->getAbsolutePosition(8,8));
    player->setMap(map);
    
    Player* player2 = prepareOpponent(spriteFactory, scene, renderer, map);
    
    this->addPlayer(player);
    this->addPlayer(player2);
    //For each player load unit and buildings data model and view resources
    
    /////////  PLAYER 1 UNITS //////////
    UnitFactory unitFactory;
    Unit* unit = unitFactory.createUnit("unit.lua");
    Sprite* unitSprite = spriteFactory->createSprite(UNIT);
    unitSprite->setModel(unit);
    Texture* unitTexture = renderer->loadSprite(unit->getResource(), 128, 82);
    unitSprite->setTexture(unitTexture);
    //resize to fit in a map tile
    unitSprite->resize(40, 40);
    unit->setPosition(map->getTile(2, 1));
    player->addUnit(unit);
    
    Unit* unit3 = unitFactory.createUnit("unit.lua");;
    Sprite* unitSprite3 = spriteFactory->createSprite(UNIT);
    unitSprite3->setModel(unit3);
    Texture* unitTexture3 = renderer->loadSprite(unit3->getResource(), 128, 82);
    unitSprite3->setTexture(unitTexture3);
    //resize to fit in a map tile
    unitSprite3->resize(40, 40);
    unit3->setPosition(map->getTile(4, 4));
    player->addUnit(unit3);
    
    Unit* unit4 = unitFactory.createUnit("unit.lua");
    Sprite* unitSprite4 = spriteFactory->createSprite(UNIT);
    unitSprite4->setModel(unit4);
    Texture* unitTexture4 = renderer->loadSprite(unit3->getResource(), 128, 82);
    unitSprite4->setTexture(unitTexture4);
    //resize to fit in a map tile
    unitSprite4->resize(40, 40);
    unit4->setPosition(map->getTile(3, 8));
    player->addUnit(unit4);
    
    ///////////  PLAYER 2 UNITS ///////////
    Unit* unit2 = new Unit();
    unit2->setResource("link.png");
    Sprite* unit2Sprite = spriteFactory->createSprite(UNIT);
    unit2->setMovement(3);
    unit2->setAttackRange(1);
    unit2->setHP(10);
    unit2Sprite->setModel(unit2);
    Texture* unit2Texture = renderer->loadSprite(unit2->getResource(), 90, 90);
    unit2Sprite->setTexture(unit2Texture);
    unit2Sprite->resize(40, 40);
    unit2->setPosition(map->getTile(13, 3));
    player2->addUnit(unit2);
    
    Unit* unit5 = new Unit();
    unit5->setResource("link.png");
    Sprite* unitSprite5 = spriteFactory->createSprite(UNIT);
    unit5->setMovement(3);
    unit5->setAttackRange(1);
    unit5->setHP(10);
    unitSprite5->setModel(unit5);
    Texture* unitTexture5 = renderer->loadSprite(unit5->getResource(), 90, 90);
    unitSprite5->setTexture(unitTexture5);
    unitSprite5->resize(40, 40);
    unit5->setPosition(map->getTile(12, 5));
    player2->addUnit(unit5);
    
    Unit* unit6 = new Unit();
    unit6->setResource("link.png");
    Sprite* unitSprite6 = spriteFactory->createSprite(UNIT);
    unit6->setMovement(3);
    unit6->setAttackRange(1);
    unit6->setHP(10);
    unitSprite6->setModel(unit6);
    Texture* unitTexture6 = renderer->loadSprite(unit6->getResource(), 90, 90);
    unitSprite6->setTexture(unitTexture6);
    unitSprite6->resize(40, 40);
    unit6->setPosition(map->getTile(11, 8));
    player2->addUnit(unit6);
    
    //Load buildings
    map->loadBuildings(spriteFactory, renderer);
    
    //When all the players resources has been setted, load the strategic info map
    map->loadInfoMap(players);
    
    //register game and player controller as an scene events listener
    scene->attachMap(map);
    
    scene->attachSprite(unit2Sprite);
    scene->attachSprite(unitSprite3);
    scene->attachSprite(unitSprite4);
    scene->attachSprite(unitSprite5);
    scene->attachSprite(unitSprite6);
    scene->attachSprite(unitSprite);
    
    scene->attachSprite(playerSprite);
    
    scene->registerListener(this);
    
    return scene;
}

Player* ProjectAI::prepareOpponent(SpriteFactory* spriteFactory, Scene* scene, Renderer* renderer, Map* map)
{
    Player* player2 = nullptr;
    if (scene->getExtras() == 0) {
        player2 = new Player(1);
    }else if(scene->getExtras() == 1){
        player2 = new PlayerAI(1, scene ,renderer);
        PlayerAI* playerAI = (PlayerAI*)player2;
        playerAI->setPlayerList(&players);
    }
    Sprite* playerSprite2 = spriteFactory->createSprite(PLAYER);
    playerSprite2->setModel(player2);
    Texture* texture2 = renderer->loadTexture("target_tile_white.png");
    texture2->setVisible(false);
    playerSprite2->setTexture(texture2);
    playerSprite2->resize(40, 40);
    texture2->setPosition(map->getAbsolutePosition(3,8));
    player2->setMap(map);
    
    scene->attachSprite(playerSprite2);
    return player2;
}

void ProjectAI::onGameStarted(SceneManager* sceneManager, Renderer* renderer)
{
    this->renderer = renderer;
    this->sceneManager = sceneManager;
    
    //Default camera
    Camera* camera = new Camera(Point(0, 0), 640, 480);
    
    Scene* menuScene = mainMenuScene(sceneManager, renderer);
    sceneManager->setActualScene(menuScene, "menu_scene");
    
    Scene* gameScene = new Scene(renderer);
    gameScene->registerCamera(camera);
    sceneManager->registerScene(gameScene, "game_scene");
    /*
    Scene* scene = gameScene(sceneManager, renderer);
    sceneManager->registerScene(scene, "game_scene");*/
}

Player* ProjectAI::nextPlayer()
{
    Player* result;
    //Set the actual active player as non active
    if(activePlayer != nullptr){
        activePlayer->setActive(false);
    }
    std::list<Player*>::iterator iterator;
    iterator = players.begin();
    if(playerTurn >= players.size()){
        playerTurn = 0;
        std::advance(iterator, playerTurn);
        day++;
        result = *iterator;
        playerTurn++;
    }else{
        std::advance(iterator, playerTurn);
        result = *iterator;
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
    //If the active player doesn't have a unity with that id then it's a enemy
    for (int i = 0; i < players.size(); i++) {
        if (activePlayer->hasUnit(id)) {
            result = UNIT_CLICKED;
        }
    }
    //TODO Handle events filters somewhere else...
    //If the sprite clicked is not a valid unit(Player sprite)
    if (activePlayer->getId() == id) {
        result = NOT_HANDLED;
    }
    return result;
}

void ProjectAI::addPlayer(Player *player)
{
    players.push_back(player);
}

Player* ProjectAI::getPlayer(int position)
{
    std::list<Player*>::iterator iterator;
    iterator = players.begin();
    std::advance(iterator, position);
    Player* player = *iterator;
    return player;
}
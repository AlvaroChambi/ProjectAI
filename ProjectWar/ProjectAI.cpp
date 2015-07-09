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
#include "HorizontalLayout.h"
#include "Button.h"
#include "MessageManager.h"
#include "DataMessage.h"

ProjectAI::ProjectAI() : activePlayer(nullptr), day(0), playerTurn(0), founds(1000)
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
            //TODO: change it so it can be notified with the message system
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
        case BUILDING_CLICKED:
            std::cout << "building clicked\n";
            playerController->onBuildingClicked(id);
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

void pushCreateViewMessage(Unit* unit)
{
    //Sends message to create the view for the unit and attach it to the scene
    DataMessage<Unit*> *message = new DataMessage<Unit*>(MESSAGE_CREATE_UNIT,unit);
    MessageManager::getInstance().sendMessage(message);
}

Scene* ProjectAI::gameScene(Scene* scene, Renderer* renderer)
{
    //UI Commands
    Layout* mainLayout = new Layout();
    mainLayout->setParams(Params(FILL, FILL, UP));
    scene->setUIHUD(mainLayout);
    //Set scene ui
    layout = new UnitUIView();
    Button* button = new Button(END_BUTTON);
    button->setParams(Params(60,40,CENTER));
    layout->setParams(Params(FILL,100,DOWN));
    mainLayout->addComponent(layout);
    layout->addComponent(button);
    button->setImageResource("end_button.bmp");
    
    //PLayer UI
    Layout* gameLayout = new VerticalLayout();
    gameLayout->setBackground(Color(0,0,0));
    foundsText = new Text();
    playerText = new Text();
    //TODO update with actual player info
    foundsText->setTextResource("Founds: " + std::to_string(founds));
    playerText->setTextResource("Player1");
    playerText->setParams(Params(50,5,CENTER));
    foundsText->setParams(Params(50,5,CENTER));
    gameLayout->setParams(Params(200,40,UP));
    
    mainLayout->addComponent(gameLayout);
    gameLayout->addComponent(foundsText);
    gameLayout->addComponent(playerText);
    
    //Factory Popup
    //TODO think a way to measure the layouts when all the childrens are already defined
    //TODO Move to factorySelectedState
    std::cout << "POP_UP_LAYOUT\n";
    //Prepare popup
    Layout* popUp = new VerticalLayout();
    popUp->setParams(Params(300,350,CENTER));
    popUp->setBackground(Color(0,255,255));
    
    scene->registerPopUp(popUp);
    
    Params params = Params(290, 110, CENTER);
    HorizontalLayout* item0 = new HorizontalLayout();
    HorizontalLayout* item1 = new HorizontalLayout();
    HorizontalLayout* item2 = new HorizontalLayout();
    
    item0->setBackground(Color(255,100,100));
    item1->setBackground(Color(255,0,255));
    item2->setBackground(Color(10,90,0));
    
    item0->setParams(params);
    item1->setParams(params);
    item2->setParams(params);

    popUp->addComponent(item0);
    popUp->addComponent(item1);
    popUp->addComponent(item2);

    Params imageParams = Params(40,40,CENTER);
    Button* item0Image = new Button(12);
    Button* item1Image = new Button(13);
    Button* item2Image = new Button(14);
    
    item0Image->setImageResource("soldier_avatar.png");
    item1Image->setImageResource("tank_avatar.png");
    item2Image->setImageResource("anti_tank_avatar.png");
    
    item0Image->setParams(imageParams);
    item1Image->setParams(imageParams);
    item2Image->setParams(imageParams);
    
    Params textParams = Params(30, 10, CENTER);
    Text* item0Text = new Text();
    Text* item1Text = new Text();
    Text* item2Text = new Text();
    
    item0Text->setTextResource("1000");
    item1Text->setTextResource("3000");
    item2Text->setTextResource("4000");
    
    item0Text->setParams(textParams);
    item1Text->setParams(textParams);
    item2Text->setParams(textParams);
    
    item0->addComponent(item0Image);
    item0->addComponent(item0Text);
    
    item1->addComponent(item1Image);
    item1->addComponent(item1Text);
    
    item2->addComponent(item2Image);
    item2->addComponent(item2Text);
    
    //Load map data model and view resources
    map = new Map();
    map->loadMap(renderer, 40, 40);
    
    spriteFactory = new SpriteFactory;
    
    //TODO fix how we set the id to the sprites and models
    Player* player = new Player(0);
    player->setMap(map);
    
    Player* player2 = prepareOpponent(spriteFactory, scene, renderer, map);
    
    this->addPlayer(player);
    this->addPlayer(player2);
    //For each player load unit and buildings data model and view resources
    
    /////////  PLAYER 1 UNITS //////////
    UnitFactory unitFactory;
    Unit* unit = unitFactory.createUnit("unit.lua");
    unit->setPosition(map->getTile(2, 1));
    player->addUnit(unit);
    pushCreateViewMessage(unit);
    
    Unit* unit3 = unitFactory.createUnit("tank.lua");;
    unit3->setPosition(map->getTile(4, 4));
    player->addUnit(unit3);
    pushCreateViewMessage(unit3);
    
    Unit* unit4 = unitFactory.createUnit("unit.lua");
    unit4->setPosition(map->getTile(3, 8));
    player->addUnit(unit4);
    pushCreateViewMessage(unit4);
    
    ///////////  PLAYER 2 UNITS ///////////
    Unit* unit2 = unitFactory.createUnit("link.lua");
    Sprite* unit2Sprite = spriteFactory->createSprite(UNIT, renderer, unit2, 90, 90);
    unit2->setPosition(map->getTile(13, 3));
    unit2Sprite->setModel(unit2);
    unit2Sprite->resize(40, 40);
    player2->addUnit(unit2);
    
    Unit* unit5 = unitFactory.createUnit("link.lua");
    Sprite* unitSprite5 = spriteFactory->createSprite(UNIT, renderer, unit5, 90, 90);
    unit5->setPosition(map->getTile(12, 5));
    unitSprite5->setModel(unit5);
    unitSprite5->resize(40, 40);
    player2->addUnit(unit5);
    
    Unit* unit6 = unitFactory.createUnit("link.lua");
    Sprite* unitSprite6 = spriteFactory->createSprite(UNIT, renderer, unit6, 90, 90);
    unit6->setPosition(map->getTile(11, 8));
    unitSprite6->setModel(unit6);
    unitSprite6->resize(40, 40);
    player2->addUnit(unit6);
    
    //Load buildings
    map->loadBuildings(spriteFactory, renderer);
    
    //When all the players resources has been setted, load the strategic info map
    map->loadInfoMap(players);
    
    //register game and player controller as an scene events listener
    scene->attachMap(map);
    
    scene->attachSprite(unit2Sprite);
    scene->attachSprite(unitSprite5);
    scene->attachSprite(unitSprite6);
    
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
    player2->setMap(map);
    return player2;
}

void ProjectAI::onGameStarted(SceneManager* sceneManager, Renderer* renderer)
{
    this->renderer = renderer;
    this->sceneManager = sceneManager;
    
    
    //Default camera
    Camera* camera = new Camera(Point(0, 0), 640, 480);
    
   // Scene* menuScene = mainMenuScene(sceneManager, renderer);
    Scene* menuScene = new MenuScene(renderer);
    menuScene->registerListener(this);
    sceneManager->setActualScene(menuScene, "menu_scene");
    
    Scene* gameScene = new GameScene(renderer);
    gameScene->registerCamera(camera);
    sceneManager->registerScene(gameScene, "game_scene");
    
    MessageManager::getInstance().registerForMessage(MESSAGE_SHOW_POPUP, new ShowPopUpCallback(sceneManager));
    MessageManager::getInstance().registerForMessage(MESSAGE_HIDE_POPUP, new HidePopUpCallback(sceneManager));
    MessageManager::getInstance().registerForMessage(MESSAGE_CREATE_UNIT, new CreateUnitCallback(this));
    MessageManager::getInstance().registerForMessage(MESSAGE_UPDATE_PLAYER_INFO, new UpdateUICallback(this));
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
    MessageManager::getInstance().sendMessage(new Message(MESSAGE_UPDATE_PLAYER_INFO));
    return result;
}

//Given an sprite id return an event according to the type of sprite clicked
Input ProjectAI::getPlayerEvent(int id)
{
    Input result = ENEMY_UNIT_CLICKED;
    
    if (map->getBuilding(id) != nullptr) {
        result = BUILDING_CLICKED;
    }
    
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

void ShowPopUpCallback::function(Message* message)
{
    sceneManager->getActualScene()->showPopup();
}

void HidePopUpCallback::function(Message* message)
{
    sceneManager->getActualScene()->hidePopUp();
}

void CreateUnitCallback::function(Message* message)
{
    DataMessage<Unit*>* dataMessage = (DataMessage<Unit*>*)message;
    Unit* unit = dataMessage->dataStorage;
    //Create view
    Sprite* unitSprite = game->spriteFactory->createSprite(UNIT, game->renderer, unit);
    unitSprite->setModel(unit);
    unitSprite->resize(40, 40);
    game->sceneManager->getActualScene()->attachSprite(unitSprite);
}

void UpdateUICallback::function(Message *message)
{
    game->playerText->setTextResource("Player " + std::to_string(game->activePlayer->getId()));
    game->foundsText->setTextResource(std::to_string(game->activePlayer->getFounds()));
}
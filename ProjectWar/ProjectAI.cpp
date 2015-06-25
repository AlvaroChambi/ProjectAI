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

Scene* ProjectAI::gameScene(Scene* scene, Renderer* renderer)
{
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
    
    Layout* gameLayout = new VerticalLayout();
    gameLayout->setBackground(Color(0,0,0));
    Text* foundsText = new Text();
    Text* playerText = new Text();
    //TODO update with actual player info
    foundsText->setTextResource("Founds: " + std::to_string(founds));
    playerText->setTextResource("Player1");
    playerText->setParams(Params(50,5,CENTER));
    foundsText->setParams(Params(50,5,CENTER));
    gameLayout->setParams(Params(200,40,UP));
    
    mainLayout->addComponent(gameLayout);
    gameLayout->addComponent(foundsText);
    gameLayout->addComponent(playerText);
    

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
    Button* item0Image = new Button(-1);
    Button* item1Image = new Button(-1);
    Button* item2Image = new Button(-1);
    
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
    
    SpriteFactory* spriteFactory = new SpriteFactory;
    
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
    Sprite* unitSprite = spriteFactory->createSprite(UNIT);
    unitSprite->setModel(unit);
    Texture* unitTexture = renderer->loadSprite(unit->getResource(), 128, 128);
    unitSprite->setTexture(unitTexture);
    //resize to fit in a map tile
    unitSprite->resize(40, 40);
    unit->setPosition(map->getTile(2, 1));
    player->addUnit(unit);
    
    Unit* unit3 = unitFactory.createUnit("tank.lua");;
    Sprite* unitSprite3 = spriteFactory->createSprite(UNIT);
    unitSprite3->setModel(unit3);
    Texture* unitTexture3 = renderer->loadSprite(unit3->getResource(), 128, 128);
    unitSprite3->setTexture(unitTexture3);
    //resize to fit in a map tile
    unitSprite3->resize(40, 40);
    unit3->setPosition(map->getTile(4, 4));
    player->addUnit(unit3);
    
    Unit* unit4 = unitFactory.createUnit("unit.lua");
    Sprite* unitSprite4 = spriteFactory->createSprite(UNIT);
    unitSprite4->setModel(unit4);
    Texture* unitTexture4 = renderer->loadSprite(unit4->getResource(), 128, 128);
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
    
    //scene->attachSprite(playerSprite);
    
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

void ShowPopUpCallback::function()
{
    sceneManager->getActualScene()->showPopup();
}

void HidePopUpCallback::function()
{
    sceneManager->getActualScene()->hidePopUp();
}
//
//  MenuScene.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 11/6/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#include "MenuScene.h"
#include "VerticalLayout.h"
#include "Button.h"


MenuScene::MenuScene(Renderer* renderer, SceneManager* manager) : Scene(renderer, manager)
{

}

MenuScene::~MenuScene()
{
    //Listen scene events ad handle them here
    //need an scene manager
}

void MenuScene::onSceneStarted()
{
    VerticalLayout* menuLayout = new VerticalLayout;
    //TODO Change the way to set the ui components id
    Button* menuButton = new Button();
    Button* menuButton2 = new Button();
    menuButton->setParams(Params(256,128,CENTER));
    menuButton2->setParams(Params(256,128,CENTER));
    //TODO Animate on click
    menuButton->setImageResource("player_player_button.png");
    menuButton2->setImageResource("player_ai_button.png");
    std::cout << "Adding menu layout\n";
    this->setUIHUD(menuLayout);
    std::cout << "Adding butttons\n";
    menuLayout->addComponent(menuButton);
    menuLayout->addComponent(menuButton2);
}

void MenuScene::onScenePaused()
{

}

void MenuScene::onSceneFinished()
{

}
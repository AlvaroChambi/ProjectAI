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


MenuScene::MenuScene(Renderer* renderer) : Scene(renderer)
{

}

MenuScene::~MenuScene()
{

}

void MenuScene::onSceneStarted()
{
  /*  Layout* layout = new Layout;
    Params params = Params(200, 200, CENTER);
    layout->setBackground(Color(255,0,0));
    layout->setParams(params);
    std::cout << "Adding menu layout\n";
    this->setUIHUD(layout);*/
    VerticalLayout* menuLayout = new VerticalLayout;
    //TODO Change the way to set the ui components id
    Button* menuButton = new Button(10);
    Button* menuButton2 = new Button(11);
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
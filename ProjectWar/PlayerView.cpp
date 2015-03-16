//
//  PlayerView.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 13/3/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#include "PlayerView.h"

PlayerView::PlayerView() : View()
{

}

PlayerView::~PlayerView()
{

}

void PlayerView::setModel(Model* model)
{
    View::setModel(model);
    this->player = (Player*)model;
}

void PlayerView::update()
{
    this->getTexture()->setPosition(player->getTile().getTexture()->getPosition());
    std::cout << "update!\n";
}


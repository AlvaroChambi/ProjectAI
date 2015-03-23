//
//  PlayerView.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 13/3/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#include "PlayerView.h"

PlayerView::PlayerView() : Sprite()
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

void PlayerView::update( Update update )
{
    switch (update) {
        case POSITION_UPDATE:
            this->getTexture()->setPosition(player->getTile().getTexture()->getPosition());
            break;
        case SELECTED_UPDATE:
            if(this->player->getSelectedUnit() != nullptr){
                this->getTexture()->setVisible(false);
            }else{
                this->getTexture()->setVisible(true);
            }
            break;
        default:
            break;
    }
}


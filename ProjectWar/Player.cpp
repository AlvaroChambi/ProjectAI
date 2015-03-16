//
//  Player.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 13/3/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#include "Player.h"

Player::Player() : Model(), position(0,0)
{
    
}

Player::~Player()
{

}

void Player::setPosition(int x, int y)
{
    position.x = x;
    position.y = y;
    this->notifyObservers();
}

Point Player::getPosition()
{
    return position;
}

void Player::setTile(const Tile tile)
{
    this->tile = tile;
    this->notifyObservers();
}

Tile Player::getTile()
{
    return tile;
}

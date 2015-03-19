//
//  Unit.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 13/3/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#include "Unit.h"

Unit::Unit() : Model(), tile(), movement(0), hp(0)
{
    
}

Unit::~Unit()
{

}

//This method does not update the texture position, maybe we have to implement it
void Unit::setPosition(int x, int y)
{
    this->tile.position.x = x;
    this->tile.position.y = y;
}

void Unit::setPosition(const Tile tile)
{
    this->tile = tile;
}

Tile Unit::getTile()
{
    return tile;
}

Point Unit::getPosition()
{
    return tile.position;
}

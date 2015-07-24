//
//  Tile.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 13/3/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#include "Tile.h"

Tile::Tile() : row(0), column(0) ,texture(nullptr), srcPosition(), destPosition(), width(0), height(0)
{
    this->texture = nullptr;
}

Tile::Tile(Texture* texture) : row(0), column(0), srcPosition(), destPosition(), width(0), height(0)
{
    this->texture = texture;
}

Tile::~Tile()
{

}

Texture* Tile::getTexture()
{
    return texture;
}

void Tile::setTexture(Texture* texture)
{
    this->texture = texture;
}

Point Tile::getPosition()
{
    return destPosition;
}

bool Tile::matchPosition(Point position)
{
    bool result = false;
    if(position.x < destPosition.x + this->width && position.x > destPosition.x){
        if(position.y < destPosition.y + this->height && position.y > destPosition.y){
            result = true;
        }
    }
    
    return result;
}

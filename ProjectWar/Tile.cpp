//
//  Tile.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 13/3/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#include "Tile.h"

Tile::Tile()
{

}

Tile::Tile(Texture* texture) : position(0,0)
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

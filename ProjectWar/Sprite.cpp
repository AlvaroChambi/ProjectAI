//
//  Sprite.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 17/3/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#include "Sprite.h"

Sprite::Sprite() : id(-1)
{

}

Sprite::~Sprite()
{

}

void Sprite::setID(int id)
{
    this->id = id;
}

int Sprite::getID()
{
    return id;
}

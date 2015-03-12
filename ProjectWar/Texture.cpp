//
//  Texture.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 10/3/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#include "Texture.h"

Texture::Texture() : width(0), height(0)
{
}

Texture::~Texture()
{

}

void Texture::setPosition(Point position)
{
    this->position = position;
}

void Texture::setPosition(int x, int y)
{
    position.x = x;
    position.y = y;
}

Point Texture::getPosition()
{
    return position;
}

void Texture::setWidth(int width)
{
    this->width = width;
}

int Texture::getWidth()
{
    return width;
}

void Texture::setHeight(int height)
{
    this->height = height;
}

int Texture::getHeight()
{
    return height;
}



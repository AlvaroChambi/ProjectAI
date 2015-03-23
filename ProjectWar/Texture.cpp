//
//  Texture.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 10/3/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#include "Texture.h"

Texture::Texture() : width(0), height(0), position(0,0), zOrder(0), sourceRect(0,0),frameWidth(0),
                     visible(true), frameHeight(0)
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

void Texture::setZOrder(int zOrder)
{
    this->zOrder = zOrder;
}

int Texture::getZOrder()
{
    return zOrder;
}

void Texture::setVisible(bool visibility)
{
    this->visible = visibility;
}

bool Texture::isVisible()
{
    return visible;
}

Point Texture::getSourceRect()
{
    return sourceRect;
}

void Texture::setSourceRect(Point position)
{
    this->sourceRect = position;
}

void Texture::setFrameWidth(int width)
{
    this->frameWidth = width;
}

int Texture::getFrameWidth()
{
    return frameWidth;
}

void Texture::setFrameHeight(int height)
{
    this->frameHeight = height;
}

int Texture::getFrameHeight()
{
    return frameHeight;
}

bool Texture::matchPosition(const Point position)
{
    bool result = false;
    if(position.x < this->position.x + this->width && position.x > this->position.x){
        if(position.y < this->position.y + this->height && position.y > this->position.y){
            result = true;
        }
    }
    
    return result;
}


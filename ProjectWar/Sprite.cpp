//
//  Sprite.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 17/3/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#include "Sprite.h"

Sprite::Sprite() : id(-1), animated(false), frame(0), width(0), height(0)
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

void Sprite::setTexture(Texture *texture)
{
    View::setTexture(texture);
    this->width = texture->getWidth();
    this->height = texture->getHeight();
}

void Sprite::updateFrame()
{
    int frameWidth = getTexture()->getFrameWidth();
    //Just animating in the "x axis"...
    if(animated){
        if (frame * frameWidth <= (getTexture()->getWidth() - frameWidth)) {
            getTexture()->setSourceRect(Point( frame * frameWidth, 0 ));
            frame++;
        }else{
            //restart the animation
            frame = 0;
        }
    }
}

//Does not respect aspect ratio
void Sprite::resize(int width, int height)
{
    this->width = width;
    this->height = height;
}

int Sprite::getWidth()
{
    return width;
}

int Sprite::getHeight()
{
    return height;
}

void Sprite::startAnimation()
{
    if(!animated){
        this->animated = true;
    }
}

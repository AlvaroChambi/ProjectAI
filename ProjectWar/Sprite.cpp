//
//  Sprite.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 8/4/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#include "Sprite.h"


Sprite::Sprite() : id(-1), animated(false), frame(0), width(0), height(0), texture(nullptr)
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
    this->texture = texture;
    this->width = texture->getFrameWidth();
    this->height = texture->getFrameHeight();
}

Texture* Sprite::getTexture()
{
    return texture;
}

void Sprite::render(Renderer *renderer)
{
 if (getTexture()->isVisible()) {
     renderer->drawTexture(getTexture(), getWidth(), getHeight());
 }
}

//Try to set a fixed frame rate for animations...
void Sprite::updateFrame()
{
    int frameWidth = getTexture()->getFrameWidth();
    //Just animating in the "x axis"...
    if(animated){
        if (frame * frameWidth <= (getTexture()->getWidth() - frameWidth)) {
            getTexture()->setFramePosition(Point( frame * frameWidth, 0 ));
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

void Sprite::updateAnimated(bool animated)
{
    this->animated = animated;
}

bool Sprite::matchPosition(Point position)
{
    bool result = false;
    int posX = this->getTexture()->getPosition().x;
    int posY = this->getTexture()->getPosition().y;
    if(position.x < posX + this->width && position.x > posX){
        if(position.y < posY + this->height && position.y > posY){
            result = true;
        }
    }
    
    return result;
}

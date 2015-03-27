//
//  Button.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 24/3/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#include "Button.h"

Button::Button(int id) : UIComponent(id), texture(nullptr)
{

}

Button::~Button()
{

}

void Button::render(Renderer *renderer)
{
    //Update texture with the adjusted values for position and dimensions
    texture->setPosition(this->getPosition());
    renderer->drawTexture(texture, this->getWidth(), this->getHeight());
}

void Button::setTexture(Texture *texture)
{
    this->texture = texture;
}

UIComponent* Button::matchEvent(Point position)
{
    UIComponent* result = nullptr;
    if (texture->matchPosition(position)) {
        result = this;
    }
    return result;
}
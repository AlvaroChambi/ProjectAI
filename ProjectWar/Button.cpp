//
//  Button.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 24/3/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#include "Button.h"

Button::Button(int id) : UIComponent(id), texture(nullptr), resource(""),resourceChanged(false)
{

}

Button::~Button()
{

}

void Button::render(Renderer *renderer)
{
    if (resourceChanged && resource != "") {
        texture = renderer->loadTexture(resource);
        resourceChanged= false;
    }
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
    if (texture != nullptr && texture->matchPosition(position)) {
        result = this;
    }
    return result;
}

void Button::setImageResource(std::string resource)
{
    this->resource = resource;
    resourceChanged = true;
}
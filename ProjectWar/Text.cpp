//
//  Text.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 2/4/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#include "Text.h"

Text::Text() : UIComponent(-1), resource(""), texture(nullptr), changed(false)
{

}

Text::Text(int id) : UIComponent(id), resource(""), texture(nullptr), changed(false)
{
    
}

Text::~Text()
{

}

void Text::render(Renderer *renderer)
{
    //if the text has been changed create new texture with the new text
    if (changed && resource != "") {
        this->texture = renderer->loadText(resource, Color(255,255,255));
        this->setWidth(texture->getWidth());
        this->setHeight(texture->getHeight());
        this->changed = false;
    }
    
    if(texture != nullptr && resource != "" && texture->isVisible()){
        texture->setPosition(getPosition().x, getPosition().y);
        renderer->drawTexture(texture);
    }
}

void Text::setVisible(bool visible)
{
    this->texture->setVisible(visible);
}

UIComponent* Text::matchEvent(Point position)
{
    UIComponent* result = nullptr;
    if (texture->matchPosition(position)) {
        result = this;
    }
    return result;
}

void Text::setTextResource(std::string text)
{
    this->resource = text;
    this->changed = true;
}
//
//  UIComponent.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 24/3/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#include "UIComponent.h"

UIComponent::UIComponent(int id) : id(id), width(0), height(0)
{

}

UIComponent::~UIComponent()
{

}

void UIComponent::setParams(Params params)
{
    this->params = params;
}

void UIComponent::setID(int id)
{
    this->id = id;
}

int UIComponent::getID()
{
    return id;
}

//updates screen(in pixels)position and dimensions of the component(needed to have a parent defined)
void UIComponent::updateValues() //Called whenever we set a parent
{
    //Make to recall this method when setting new parent for this or any component above
    this->updateDimensions();
    this->updatePosition();
}

void UIComponent::updateDimensions()
{
    switch (params.width) {
        case FILL:
            this->width = parent->width;
            break;
        default:
            this->width = params.width;
            break;
    }
    
    switch (params.height) {
        case FILL:
            this->height = parent->height;
            break;
        default:
            this->height = params.height;
            break;
    }
}

void UIComponent::updatePosition()
{
    switch (params.gravity) {
        case CENTER:
        {
            int centerX = parent->position.x + parent->getWidth() / 2;
            int centerY = parent->position.y + parent->getHeight() / 2;
            int offsetX = width / 2;
            int offsetY = height / 2;
            this->setPosition(centerX - offsetX, centerY -offsetY);
            break;
        }
        case UP:
        {
            int y = parent->position.y;
            this->setPosition(position.x, y);
        }
            break;
        case DOWN:
        {
            int y = parent->position.y + parent->getHeight() - height;
            this->setPosition(position.x , y);
        }
            break;
        default:
            break;
    }
}

void UIComponent::setPosition(int x, int y)
{
    this->position.x = x;
    this->position.y = y;
}

Point UIComponent::getPosition()
{
    return position;
}

void UIComponent::setWidth(int width)
{
    this->width = width;
}

int UIComponent::getWidth()
{
    return width;
}

void UIComponent::setHeight(int height)
{
    this->height = height;
}

int UIComponent::getHeight()
{
    return height;
}

void UIComponent::setParent(UIComponent *component)
{
    this->parent = component;
    this->updateValues();
}

UIComponent* UIComponent::getParent()
{
    return parent;
}

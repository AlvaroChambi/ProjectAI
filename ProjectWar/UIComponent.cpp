//
//  UIComponent.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 24/3/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#include "UIComponent.h"

UIComponent::UIComponent(int id) : id(id), width(0), height(0), hud(false), visible(true)
{

}

UIComponent::~UIComponent()
{

}

void UIComponent::setHUD(bool hud)
{
    this->hud = hud;
}

bool UIComponent::isHUD()
{
    return hud;
}

void UIComponent::setParams(Params params)
{
    this->params = params;
}


Params UIComponent::getParams()
{
    return this->params;
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

//TODO: let the layout set the children positions, no te item itself...
void UIComponent::updatePosition()
{
    switch (params.gravity) {
        case CENTER:
        {
            center(parent->getPosition(), parent->getWidth(), parent->getHeight());
            break;
        }
        case UP:
        {
            up(parent->getPosition(), parent->getWidth(), parent->getHeight());
        }
            break;
        case DOWN:
        {
            down(parent->getPosition(), parent->getWidth(), parent->getHeight());
        }
            break;
        case CENTER_DOWN:
        {
            centerDown(parent->getPosition(), parent->getWidth(), parent->getHeight());
        }
            break;
        default:
            break;
    }
}

void UIComponent::centerDown(Point parentPosition, int parentWidth, int parentHeight)
{
    down(parentPosition, parentWidth, parentHeight);
    center(getPosition(), parentWidth, getHeight());
}

void UIComponent::center(Point parentPosition, int parentWidth, int parentHeight)
{
    int centerX = parentPosition.x + parentWidth / 2;
    int centerY = parentPosition.y + parentHeight / 2;
    int offsetX = width / 2;
    int offsetY = height / 2;
    this->setPosition(centerX - offsetX, centerY - offsetY);
}

void UIComponent::down(Point parentPosition, int parentWidth, int parentHeight)
{
    int y = parentPosition.y + parentHeight - height;
    this->setPosition(parentPosition.x, y);
}

void UIComponent::up(Point parentPosition, int parentWidth, int parentHeight)
{
    int y = parentPosition.y;
    this->setPosition(parentPosition.x, y);
}

void UIComponent::setPosition(int x, int y)
{
    this->position.x = x;
    this->position.y = y;
}

void UIComponent::setPosition(Point position)
{
    this->position = position;
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

bool UIComponent::isVisible()
{
    return visible;
}

void UIComponent::setVisible(bool visible)
{
    this->visible = visible;
}

void UIComponent::setParent(UIComponent *component)
{
    this->parent = component;
    //TODO: moved to addComponent
    //this->updateValues();
}

UIComponent* UIComponent::getParent()
{
    return parent;
}

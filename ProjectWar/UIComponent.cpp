//
//  UIComponent.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 24/3/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#include "UIComponent.h"

UIComponent::UIComponent(int id) : id(id), width(0), height(0), hud(false), visible(true), texture(nullptr)
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

void UIComponent::render(Renderer *renderer)
{
    //Update texture with the adjusted values for position and dimensions
    if (texture!=nullptr && texture->isVisible()) {
        texture->setPosition(position);
        renderer->drawTexture(texture, width, height);
    }
}

UIComponent* UIComponent::matchEvent(Point position)
{
    UIComponent* result = nullptr;
    if (texture->matchPosition(position)) {
        result = this;
    }
    return result;
}

void UIComponent::measureDimension()
{
    switch (params.width) {
        case FILL:
            this->width = parent->width;
            break;
        case WRAP:
            this->width = texture->getWidth();
            break;
        default:
            this->width = params.width;
            break;
    }
    
    switch (params.height) {
        case FILL:
            this->height = parent->height;
            break;
        case WRAP:
            this->height = texture->getHeight();
            break;
        default:
            this->height = params.height;
            break;
    }}


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
}

UIComponent* UIComponent::getParent()
{
    return parent;
}

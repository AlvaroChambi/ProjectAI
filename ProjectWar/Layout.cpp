//
//  Layout.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 24/3/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#include "Layout.h"

Layout::Layout() : background(nullptr)
{

}

Layout::~Layout()
{

}

void Layout::render(Renderer* renderer)
{
    //If background defined render
    if( background != nullptr ){
        background->setPosition(this->getPosition());
        renderer->drawTexture(background, getWidth(), getHeight());
    }
    for (int i = 0; i < components.getSize(); i++) {
        components.getElement(i)->render(renderer);
    }
}

void Layout::addComponent(UIComponent *component)
{
    components.add(component);
    //Update parent value: first use of the params
    component->setParent(this);
    this->updatePosition();
}

void Layout::setBackground(Texture *background)
{
    this->background = background;
}


void Layout::updatePosition()
{
    
    for(int i=0; i < components.getSize();i++){
        components.getElement(i)->updateValues();
        switch (components.getElement(i)->getParams().gravity) {
            case CENTER:
            {
                int centerX = this->getPosition().x + this->getWidth() / (components.getSize()+1);
                int centerY = this->getPosition().y + this->getHeight() / 2;
                int offsetX = components.getElement(i)->getParams().width / 2;
                int offsetY = components.getElement(i)->getParams().height / 2;
                components.getElement(i)->setPosition(centerX*(i+1) - offsetX, centerY -offsetY);
                break;
            }
            case UP:
                break;
            case DOWN:
            {
 
                //int y = parent->getHeight() - height;
                //this->setPosition(position.x , y);
            }
                break;
            default:
                break;
        }
    }
}

//Not really sure if this will work with more layouts and buttons...
UIComponent* Layout::matchEvent(Point position)
{
    UIComponent* result = nullptr;
    for (int i = 0; i < components.getSize(); i++) {
        result = components.getElement(i)->matchEvent(position);
    }
    return result;
}

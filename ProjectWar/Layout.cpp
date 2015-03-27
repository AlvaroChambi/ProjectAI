//
//  Layout.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 24/3/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#include "Layout.h"

//Instancing an layout with an undefined id
Layout::Layout() : UIComponent(-1), background(nullptr)
{

}

Layout::Layout(int id) : UIComponent(id), background(nullptr)
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
}

void Layout::setBackground(Texture *background)
{
    this->background = background;
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

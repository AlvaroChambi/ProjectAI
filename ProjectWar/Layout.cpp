//
//  Layout.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 24/3/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#include "Layout.h"

Layout::Layout() : numComponents(0), background(nullptr)
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
    for (int i = 0; i < numComponents; i++) {
        components[i]->render(renderer);
    }
}

void Layout::addComponent(UIComponent *component)
{
    components[numComponents] = component;
    numComponents++;
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
    for (int i = 0; i < numComponents; i++) {
        result = components[i]->matchEvent(position);
    }
    return result;
}

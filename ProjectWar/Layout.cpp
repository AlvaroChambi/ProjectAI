//
//  Layout.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 24/3/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#include "Layout.h"

//Instancing an layout with an undefined id
Layout::Layout() : UIComponent(-1), background(nullptr), backgroundColor(nullptr)
{

}

Layout::Layout(int id) : UIComponent(id), background(nullptr), backgroundColor(nullptr)
{

}

Layout::~Layout()
{

}

void Layout::render(Renderer* renderer)
{
    if (this->isVisible()) {
        //If background color defined
        if (backgroundColor != nullptr) {
            background = renderer->loadShape(RECTANGLE, *backgroundColor, this->getWidth(), this->getHeight());
            background->hud = this->isHUD();
        }
        //If background defined render
        if( background != nullptr ){
            background->setPosition(this->getPosition());
            renderer->drawTexture(background, getWidth(), getHeight());
        }
        for (UIComponent* component : components) {
            component->render(renderer);
        }
    }
}

void Layout::addComponent(UIComponent *component)
{
    components.push_back(component);
    //update children hud value
    component->setHUD(this->isHUD());
    //Update parent value: first use of the params
    component->setParent(this);
}

void Layout::cleanComponents()
{
    this->components.clear();
}

void Layout::setBackground(Texture *background)
{
    background->hud = this->isHUD();
    this->background = background;
}

void Layout::setBackground(Color color)
{
    this->backgroundColor = new Color(color.r,color.g,color.b);
}

//Not really sure if this will work with more layouts and buttons...
UIComponent* Layout::matchEvent(Point position)
{
    UIComponent* result = nullptr;
    if(isVisible()){
        for (UIComponent* component : components) {
            result = component->matchEvent(position);
            //Stop when i found a match, i dont really like the way i'm doing this...
            if (result != nullptr) {
                return result;
            }
        }
    }
    return result;
}

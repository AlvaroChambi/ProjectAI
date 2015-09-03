//
//  Layout.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 24/3/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#include "Layout.h"

//Instancing an layout with an undefined id
Layout::Layout() : UIComponent(), background(nullptr), backgroundColor(nullptr)
{

}

Layout::~Layout()
{

}

void Layout::render(Renderer* renderer)
{
    //UIComponent::render(renderer);
    renderer->renderDrawShape(RECTANGLE_OUTLINE, position, Color(255, 0, 0), width, height);
    
    if (this->isVisible()) {
        //If background color defined
        if (backgroundColor != nullptr) {
            background = renderer->loadShape(RECTANGLE, *backgroundColor, this->getWidth(), this->getHeight());
            background->hud = this->isHUD();
        }
        //If background defined 
        if( background != nullptr ){
            background->setPosition(this->getPosition());
            renderer->drawTexture(background, getWidth(), getHeight());
        }
        for (UIComponent* component : components) {
            component->render(renderer);
        }
    }
}

//measure the distribution of the layout
void Layout::measureDisposition()
{
    for (UIComponent* component : components) {
        component->measurePosition(position, width, height);
    }
}

void Layout::populateLayout(std::vector<Point> dispositionPoints)
{
    std::list<UIComponent*>::const_iterator iterator;
    for (iterator = components.begin(); iterator != components.end(); ++iterator) {
        std::cout << *iterator;
    }
    
    int i = 0;
    for (UIComponent* component : components) {
        Point start = dispositionPoints.at(i++);
        Point end = dispositionPoints.at(i++);
        component->measurePosition(start, end.x - start.x, end.y - start.y);
    }
}

void Layout::addComponent(UIComponent *component)
{
    components.push_back(component);
    //update children hud value
    component->setHUD(this->isHUD());
    //Update parent value: first use of the params
    component->setParent(this);
    
    //Dimension are not dependant on the type of layout
    component->measureDimension();
    //Position measure must consider the type of layout and the items in it
    this->measureDisposition();
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

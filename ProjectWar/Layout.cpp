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

//When the layout and dimensions and position has been succesfully measured
void Layout::onMeasureCompleted()
{
    this->measureDisposition();
}

//Whenever a layout dimensions or position is changed
void Layout::onMeasureChanged()
{
    this->measureDisposition();
}

void Layout::resize(float widthRatio, float heightRatio)
{
    UIComponent::resize(widthRatio, heightRatio);
    for (UIComponent* component : components) {
        component->resize(widthRatio, heightRatio);
        component->onMeasureChanged();
    }
    onMeasureChanged();
}

//measure the distribution of the layout and places his components
void Layout::measureDisposition()
{
    std::vector<Point> dispositionPoints = layoutDisposition();
    assignFrames(dispositionPoints);
    populateLayout(dispositionPoints);
}

void Layout::populateLayout(std::vector<Point> dispositionPoints)
{
    for (UIComponent* component : components) {
        Frame frame = component->frame;
        component->measurePosition(frame.position, frame.width, frame.height);
        //Notify finished measurement
        component->onMeasureCompleted();
    }
}

void Layout::assignFrames(std::vector<Point> dispositionPoints)
{
    std::vector<UIComponent*> vector(components.begin(), components.end());
    assignFrames(dispositionPoints, vector);
}

void Layout::assignFrames(std::vector<Point> dispositionPoints, std::vector<UIComponent*> components)
{
    int i = 0;
    for (UIComponent* component : components) {
        Point start = dispositionPoints.at(i++);
        Point end = dispositionPoints.at(i++);
        component->frame.position = start;
        component->frame.width = end.x - start.x;
        component->frame.height = end.y - start.y;
    }
}

std::vector<Point> Layout::layoutDisposition()
{
    std::vector<Point> dispositionPoints;
    for (int i = 0; i < components.size(); i++) {
        Point start(position);
        Point end(position.x + width, position.y + height);
        dispositionPoints.push_back(start);
        dispositionPoints.push_back(end);
    }
    return dispositionPoints;
}

void Layout::addComponent(UIComponent *component)
{
    components.push_back(component);
    //update children hud value
    component->setHUD(this->isHUD());
    //Update parent value: first use of the params
    component->setParent(this);
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

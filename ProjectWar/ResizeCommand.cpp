//
//  ResizeCommand.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 17/9/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#include "ResizeCommand.h"
#include "UIComponent.h"

ResizeCommand::ResizeCommand(UIComponent* component, float widthRatio, float heightRatio)
: widthRatio(widthRatio), heightRatio(heightRatio), component(component)
{
}

ResizeCommand::~ResizeCommand()
{

}

void ResizeCommand::execute()
{
    this->width = component->width;
    this->height = component->height;
    
    resize(widthRatio, heightRatio);
}

void ResizeCommand::cancel()
{
    component->width = width;
    component->height = height;
}

void ResizeCommand::resize(float widthRatio, float heightRatio)
{
    //Resize according to the given ratio
    //update texture dimension to match the component
    if (widthRatio < 0) {
        widthRatio = 0;
    }
    if (heightRatio < 0) {
        heightRatio = 0;
    }
    component->width = component->width * widthRatio;
    component->height = component->height * heightRatio;
}
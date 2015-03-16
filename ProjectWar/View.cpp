//
//  View.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 13/3/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#include "View.h"

View::View()
{
    
}

View::~View()
{

}

Texture* View::getTexture()
{
    return texture;
}

void View::setTexture(Texture *texture)
{
    this->texture = texture;
}

void View::setModel(Model* model)
{
    model->registerObserver(this);
}
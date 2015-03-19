//
//  UnitView.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 17/3/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#include "UnitView.h"

UnitView::UnitView() : Sprite()
{

}

UnitView::~UnitView()
{

}

void UnitView::setModel(Model *model)
{
    //Link game object id with the model id
    this->unit = (Unit*)model;
    model->setid(this->getID());
}

void UnitView::update()
{
    std::cout << "UnitView update\n";
    this->getTexture()->setPosition(unit->getTile().getTexture()->getPosition());
}
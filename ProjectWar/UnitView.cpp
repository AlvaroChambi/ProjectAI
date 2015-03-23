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
    View::setModel(model);
    //Link game object id with the model id
    this->unit = (Unit*)model;
    model->setid(this->getID());
}

void UnitView::update( Update update )
{
    switch (update) {
        case POSITION_UPDATE:
            this->getTexture()->setPosition(unit->getTile().getTexture()->getPosition());
            break;
        case SELECTED_UPDATE:
            this->updateAnimated(this->unit->isSelected());
            break;
        case ACTIVE_UPDATE:
            this->updateAnimated(false);
            break;
        default:
            break;
    }
}
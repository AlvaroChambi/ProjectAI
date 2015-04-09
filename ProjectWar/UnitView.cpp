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
    text = new Text();
    text->setParams(Params(10,10,DOWN));
    text->updateDimensions();
}

UnitView::~UnitView()
{

}

void UnitView::setModel(Model *model)
{
    model->registerObserver(this);
    //Link game object id with the model id
    this->unit = (Unit*)model;
    model->setid(this->getID());
    
    text->setTextResource(std::to_string(unit->getHP()));
}

void UnitView::render(Renderer *renderer)
{
    Sprite::render(renderer);
    text->render(renderer);
}

void UnitView::update( Update update )
{
    switch (update) {
        case POSITION_UPDATE:
            this->getTexture()->setPosition(unit->getTile().getTexture()->getPosition());
            //Updating hp text position when the unit change his position
            text->down(getTexture()->getPosition(), this->getWidth(), this->getHeight());
            break;
        case SELECTED_UPDATE:
            this->updateAnimated(this->unit->isSelected());
            break;
        case ACTIVE_UPDATE:
            this->updateAnimated(false);
            break;
        case HP_UPDATE:
            text->setTextResource(std::to_string(unit->getHP()));
            //TODO if the unit hp is 0 or lower remove the unit graphic resources
            break;
        default:
            break;
    }
}
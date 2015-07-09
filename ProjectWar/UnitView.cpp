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
    this->getTexture()->setPosition(unit->getTile().getTexture()->getPosition());
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
            text->centerDown(getTexture()->getPosition(), this->getWidth(), this->getHeight());
            break;
        case SELECTED_UPDATE:
            this->updateAnimated(this->unit->isSelected());
            break;
        case ACTIVE_UPDATE:
            this->updateAnimated(false);
            break;
        case HP_UPDATE:
            text->setTextResource(std::to_string(unit->getHP()));
            break;
        case STATE_UPDATE:
            if(unit->getHP() == 0){
                //Remove sprite or just hide
                //TODO implement a UnitView method that hides or cleans all his resources
                this->getTexture()->setVisible(false);
                this->text->setVisible(false);
            }else{
                //Set the sprite visible again
                this->getTexture()->setVisible(true);
                this->text->setVisible(true);
            }
            break;
        default:
            break;
    }
}
//
//  BuildingView.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 11/4/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#include "BuildingView.h"

BuildingView::BuildingView() : Sprite(), building(nullptr)
{
    text = new Text;
}

BuildingView::~BuildingView()
{

}

void BuildingView::render(Renderer *renderer)
{
    Sprite::render(renderer);
    text->render(renderer);
}

void BuildingView::setModel(Model *model)
{
    model->registerObserver(this);
    //Link game object id with the model id
    this->building = (Building*) model;
    model->setid(this->getID());
    std::string string = std::to_string(building->getCaptureValue())+ "/"
    + std::to_string(building->getCapturePoints());
    text->setTextResource(string);
}

void BuildingView::update(Update update)
{
    switch (update) {
        case POSITION_UPDATE:
            this->getTexture()->setPosition(building->getTile().getPosition());
            text->center(getTexture()->getPosition(), getWidth(), getHeight());
            break;
        case CAPTURE_UPDATE:
        {
            //If the building is ocupated set the occupying player texture
            std::string string = std::to_string(building->getCaptureValue())+ "/"
            + std::to_string(building->getCapturePoints());
            text->setTextResource(string);
            
            if (building->getCaptureValue() == building->getCapturePoints()) {
                updateBuildingOwner();
            }else{
                //if no one has completed the capture the building sprite is set to neutral
                setRenderFrame(Point(0,0));
            }
        }
            break;
        default:
            break;
    }
}

void BuildingView::updateBuildingOwner()
{
    //TODO Change this, just for test...
    const int PLAYER_ONE = 0;
    const int PLAYER_TWO = 1;
    const int NEUTRAL = -1;
    
    switch (building->getOwnerID()) {
        case NEUTRAL:
            setRenderFrame(Point(0,0));
            break;
        case PLAYER_ONE:
            setRenderFrame(Point(1,0));
            break;
        case PLAYER_TWO:
            setRenderFrame(Point(2,0));
            break;
        default:
            
            break;
    }
}
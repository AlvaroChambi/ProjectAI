//
//  SpriteFactory.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 17/3/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#include "SpriteFactory.h"
#include "BuildingView.h"

SpriteFactory::SpriteFactory() : idCount(0)
{

}

SpriteFactory::~SpriteFactory()
{

}

Sprite* SpriteFactory::createSprite(SpriteType type)
{
    Sprite* sprite = nullptr;
    switch (type) {
        case UNIT:
            sprite = new UnitView();
            sprite->setID(idCount++);
            break;
        case PLAYER:
            sprite = new PlayerView();
            sprite->setID(idCount++);
            break;
        case BUILDING:
            sprite = new BuildingView();
            sprite->setID(idCount++);
        default:
            break;
    }
    return sprite;
}
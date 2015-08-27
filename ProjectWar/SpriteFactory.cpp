//
//  SpriteFactory.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 17/3/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#include "SpriteFactory.h"
#include "BuildingView.h"

//TODO think a better way to assign an id to the game objects
SpriteFactory::SpriteFactory() : idCount(1)
{

}

SpriteFactory::~SpriteFactory()
{

}

//Default frame width and height = 128
Sprite* SpriteFactory::createSprite(SpriteType type, Renderer* renderer, Unit* unit)
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
    Texture* unitTexture = renderer->loadSprite(unit->getResource(), 32, 32);
    sprite->setTexture(unitTexture);
    return sprite;
}

Sprite* SpriteFactory::createSprite(SpriteType type, Renderer* renderer, Unit* unit, int frameWidth, int frameHeight)
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
    Texture* unitTexture = renderer->loadSprite(unit->getResource(), frameWidth, frameHeight);
    sprite->setTexture(unitTexture);
    return sprite;
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
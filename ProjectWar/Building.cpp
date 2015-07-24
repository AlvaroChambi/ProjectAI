//
//  Building.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 11/4/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#include "Building.h"

Building::Building() : Model(), tile(nullptr), capturePoints(0), captureValue(0), type("")
{

}

Building::~Building()
{

}

Tile Building::getTile()
{
    return tile;
}

Point Building::getPosition()
{
    return Point(tile.column, tile.row);
}

void Building::setType(std::string type)
{
    this->type = type;
}

std::string Building::getType()
{
    return type;
}

void Building::setPosition(Tile position)
{
    this->tile = position;
    this->notifyObservers(POSITION_UPDATE);
}

void Building::setCapturePoints(int value)
{
    this->capturePoints = value;
}

int Building::getCapturePoints()
{
    return capturePoints;
}

//capture value could never be higher than the capture point of the building
void Building::setCaptureValue(int value)
{
    if (value > capturePoints) {
        value = capturePoints;
    }
    this->captureValue = value;
    this->notifyObservers(CAPTURE_UPDATE);
}

int Building::getCaptureValue()
{
    return captureValue;
}

void Building::setOwnerID(int id)
{
    this->ownerID = id;
}

int Building::getOwnerID()
{
    return ownerID;
}

//returns wether the building is capture for the given player or not
bool Building::isCaptured(int playerID)
{
    bool result = false;
    if(captureValue == capturePoints && ownerID == playerID){
        result = true;
    }
    return result;
}


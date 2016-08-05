//
//  Building.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 11/4/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#include "Building.h"

Building::Building()
: Model(), capturePoints( 0 ), captureValue( 0 ) {

}

Building::Building( const Building& building ) {
    this->ownerID = building.ownerID;
    this->tile = building.tile;
    this->capturePoints = building.getCapturePoints();
    this->captureValue = building.getCaptureValue();
    setid( building.getId() );
}

Tile Building::getTile() const {
    return tile;
}

Point Building::getPosition() const {
    return tile.position;
}

void Building::setPosition( const Tile& position ) {
    this->tile = position;
    this->notifyObservers(POSITION_UPDATE);
}

void Building::setCapturePoints( int value ) {
    this->capturePoints = value;
}

int Building::getCapturePoints() const {
    return capturePoints;
}

//capture value could never be higher than the capture point of the building
void Building::setCaptureValue( int value ) {
    if (value > capturePoints) {
        value = capturePoints;
    }
    this->captureValue = value;
    this->notifyObservers(CAPTURE_UPDATE);
}

int Building::getCaptureValue() const {
    return captureValue;
}

void Building::setOwnerID( int id ) {
    this->ownerID = id;
}

int Building::getOwnerID() const {
    return ownerID;
}

//returns wether the building is capture for the given player or not
bool Building::isCaptured( int playerID ) const {
    bool result = false;
    if( captureValue == capturePoints && ownerID == playerID ) {
        result = true;
    }
    return result;
}


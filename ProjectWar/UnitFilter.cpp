//
//  UnitMovementFilter.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 1/6/16.
//  Copyright © 2016 Alvaro Chambi Campos. All rights reserved.
//

#include "UnitFilter.h"

UnitMovementFilter::UnitMovementFilter( Iterator* filter,
                                        IMap* map, Unit* unit )
: IteratorFilter( filter ) {
    this->map = (Map*)map;
    this->unit = unit;
}

bool UnitMovementFilter::isValid( Point position ) {
    bool valid = map->isValidPosition( position )
    && unit->onRange( position, unit->getMovement() );
    
    return iterator->isValid( position )
            && !isInvalidated( position ) && valid;
}

bool UnitMovementFilter::isInvalidated( Point position ) {
    bool invalidated =
        std::find( invalidatedPositions.begin(),
                   invalidatedPositions.end(),
                   position) != invalidatedPositions.end();
    if( !invalidated ) {
        invalidatedPositions.push_back( position );
    }
    return invalidated;
}

std::vector<Point>& UnitMovementFilter::getInvalidatedPositions() {
    return invalidatedPositions;
}

void UnitMovementFilter::setInvalidatedPositions(
                                    std::vector<Point> &invalidatedPositions) {
    this->invalidatedPositions = invalidatedPositions;
}
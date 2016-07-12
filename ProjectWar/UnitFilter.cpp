//
//  UnitMovementFilter.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 1/6/16.
//  Copyright © 2016 Alvaro Chambi Campos. All rights reserved.
//

#include "UnitFilter.h"

UnitMovementFilter::UnitMovementFilter( Iterator& filter,
                                        MapContext& map, const Unit& unit )
: IteratorFilter( filter ), unit( unit ), map( map ) {
}

bool UnitMovementFilter::isValid( const Point& position ) {
    bool valid = map.isValidPosition( position )
    && unit.getPosition().onRange( position, unit.getMovement() );
    
    return iterator.isValid( position ) && valid;
}
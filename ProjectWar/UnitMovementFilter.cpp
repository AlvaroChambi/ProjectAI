//
//  UnitMovementFilter.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 1/6/16.
//  Copyright © 2016 Alvaro Chambi Campos. All rights reserved.
//

#include "UnitMovementFilter.h"

UnitMovementFilter::UnitMovementFilter( Map* map, Unit* unit )
: map( map ), unit( unit ) {
    
}

UnitMovementFilter::~UnitMovementFilter() {

}

bool UnitMovementFilter::isValid( Point position ) {
    return map->isValidPosition( position )
    && unit->onRange( position, unit->getMovement() );
}
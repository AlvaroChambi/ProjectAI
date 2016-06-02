//
//  UnitMovementFilter.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 1/6/16.
//  Copyright © 2016 Alvaro Chambi Campos. All rights reserved.
//

#include "UnitFilter.h"

UnitMovementFilter::UnitMovementFilter( Iterator* filter,
                                        Map* map, Unit* unit )
: IteratorFilter( filter ) {
    this->map = map;
    this->unit = unit;
}

bool UnitMovementFilter::isValid( Point position ) {
    bool valid = map->isValidPosition( position )
    && unit->onRange( position, unit->getMovement() );
    
    return valid && iterator->isValid( position );
}

AttackRangeFilter::AttackRangeFilter( Iterator* filter, Unit* target,
                                      int attackerRange )
: IteratorFilter( filter ){
    this->target = target;
    this->attackerRange = attackerRange;
}

bool AttackRangeFilter::isValid( Point position ) {
    bool valid = target->onRange( position , attackerRange );
    return valid && iterator->isValid( position );
}
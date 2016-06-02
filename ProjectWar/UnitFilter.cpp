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
    
    return iterator->isValid( position ) && valid;
}

AttackRangeFilter::AttackRangeFilter( Iterator* filter, Unit* target,
                                      int attackerRange )
: IteratorFilter( filter ){
    this->target = target;
    this->attackerRange = attackerRange;
}

bool AttackRangeFilter::isValid( Point position ) {
    return iterator->isValid( position ) &&
        target->onRange( position , attackerRange );
}
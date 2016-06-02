//
//  UnitMovementFilter.h
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 1/6/16.
//  Copyright © 2016 Alvaro Chambi Campos. All rights reserved.
//

#ifndef UnitMovementFilter_h
#define UnitMovementFilter_h

#include "IteratorFilter.h"
#include "Map.h"
#include "Unit.h"

class UnitMovementFilter : public IteratorFilter {
public:
    UnitMovementFilter( Iterator* filter, Map* map, Unit* unit );
    
    bool isValid( Point position );
private:
    Map* map;
    Unit* unit;
};

class AttackRangeFilter : public IteratorFilter {
public:
    AttackRangeFilter( Iterator* filter, Unit* unit,
                       int attackerRange );
    
    bool isValid( Point position );
private:
    Unit* target;
    int attackerRange;
};

#endif /* UnitMovementFilter_h */

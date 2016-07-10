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
    UnitMovementFilter( Iterator& filter, MapContext* map,
                        const Unit& unit );
    
    bool isValid( const Point& position );
private:
    Map* map;
    const Unit& unit;
};

#endif /* UnitMovementFilter_h */
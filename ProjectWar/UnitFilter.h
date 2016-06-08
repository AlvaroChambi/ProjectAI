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
    UnitMovementFilter( Iterator* filter, IMap* map, Unit* unit );
    
    bool isInvalidated( Point position );
    bool isValid( Point position );
    
    std::vector<Point>& getInvalidatedPositions();
    void setInvalidatedPositions(
                        std::vector<Point>& invalidatedPositions );
private:
    Map* map;
    Unit* unit;
    std::vector<Point> invalidatedPositions;
};

#endif /* UnitMovementFilter_h */
//
//  AreaIterator.h
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 1/6/16.
//  Copyright © 2016 Alvaro Chambi Campos. All rights reserved.
//

#ifndef AreaIterator_h
#define AreaIterator_h

#include "IteratorFilter.h"
#include "Point.h"

class AreaIterator {
public:
    AreaIterator();
    AreaIterator( IteratorFilter* iteratorFilter );
    ~AreaIterator();
    
    void buildArea( Point origin, int range,
                    int maxWidth, int maxHeight );
    
    bool hasNext();
    Point next();
    
private:
    int currentPosition;
    IteratorFilter* iteratorFilter;
    
    bool hasCached;
    Point cached;
    
    int maxWidth;
    int maxHeight;
    
    Point start;
    Point end;
    
    int xOffset, yOffset;
};

#endif /* AreaIterator_h */

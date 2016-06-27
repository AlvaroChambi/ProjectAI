//
//  IteratorFilter.h
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 1/6/16.
//  Copyright © 2016 Alvaro Chambi Campos. All rights reserved.
//

#ifndef IteratorFilter_h
#define IteratorFilter_h

#include "Point.h"
#include "Iterator.h"

class IteratorFilter : public Iterator {
public:
    IteratorFilter( Iterator& iterator );
    bool hasNext();
    const Point& next();
protected:
    Iterator& iterator;
    
    bool nextSaved;
    Point savedNext;
};

#endif /* IteratorFilter_h */

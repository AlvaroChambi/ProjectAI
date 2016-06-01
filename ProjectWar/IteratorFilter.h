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

class IteratorFilter {
public:
    virtual bool isValid( Point position ) = 0;
};

#endif /* IteratorFilter_h */

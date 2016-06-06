//
//  Iterator.h
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 02/06/16.
//  Copyright (c) 2016 Alvaro Chambi Campos. All rights reserved.
//

#ifndef ProjectWar_Iterator_h
#define ProjectWar_Iterator_h

#include "Point.h"

class Iterator {
public:
    virtual bool hasNext() = 0;
    virtual Point next() = 0;
    virtual bool isValid( Point position ) = 0;
};

#endif

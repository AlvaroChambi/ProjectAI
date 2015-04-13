//
//  Point.h
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 10/3/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#ifndef __ProjectWar__Point__
#define __ProjectWar__Point__

#include <stdio.h>
#include <iostream>

class Point
{
    
public:
    int x;
    int y;
    int z;
    Point() : x(0), y(0), z(0)
    {}
    
    Point( int x, int y )
    {
        this->x = x;
        this->y = y;
    }
    
    void setZ ( int z )
    {
        this->z = z;
    }
    
    bool operator ==(Point point)
    {
        bool result= false;
        if ( x == point.x && y == point.y) {
            result = true;
        }
        return result;
    }
};

#endif /* defined(__ProjectWar__Point__) */

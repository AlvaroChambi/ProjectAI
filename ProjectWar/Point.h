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
#include <ostream>

class Point {
    
public:
    int x;
    int y;
    int z;
    bool invalidated;
    
    Point() : x(0), y(0), z(0), invalidated( false ) {
    
    }
    
    Point( int x, int y ) : Point() {
        this->x = x;
        this->y = y;
    }
    
    void setZ ( int z ) {
        this->z = z;
    }
    
    bool isValid( int xLimit, int yLimit ) const {
        if( x >= 0 && x <= xLimit && y >= 0 && y <= yLimit ) {
            return true;
        }
        return false;
    }
    
    bool isValid() {
        if( x >= 0 && y >= 0 ) {
            return true;
        }
        return false;
    }
    
    bool operator ==( const Point& point ) const {
        bool result= false;
        if ( x == point.x && y == point.y) {
            result = true;
        }
        return result;
    }
    
    bool operator !=( const Point& point ) const {
        bool result= false;
        if ( x != point.x || y != point.y) {
            result = true;
        }
        return result;
    }
    
    friend std::ostream& operator<<( std::ostream& os, const Point& point ) {
        os << "( "<< point.x << " , " << point.y << " )";
        return os;
    }
    
    int distance( const Point& point ) const {
        return std::abs( point.x - this->x ) +
        std::abs( point.y - this->y );
    }
    
    bool onRange( const Point& destination, int range ) const {
        if( distance( destination ) <= range ) {
            return true;
        }
        return false;
    }
};

#endif /* defined(__ProjectWar__Point__) */

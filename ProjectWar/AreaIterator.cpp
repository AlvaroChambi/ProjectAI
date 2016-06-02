//
//  AreaIterator.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 1/6/16.
//  Copyright © 2016 Alvaro Chambi Campos. All rights reserved.
//

#include "AreaIterator.h"
#include "GameException.h"

AreaIterator::AreaIterator()
: currentPosition( 0 ), hasCached( false ), area( nullptr ) {

}

AreaIterator::~AreaIterator() {

}

bool AreaIterator::isValid( Point position ) {
    //All values are considered valid for the main iterator
    return true;
}

void AreaIterator::buildArea( Point position,
                             int range, int maxWidth, int maxHeight ) {
    std::pair<Point, Point>* boundingArea = new std::pair<Point, Point>();
    Point start, end;
    if( position.isValid( maxWidth , maxHeight ) && range > 0 ) {
        start.x = position.x - range;
        start.y = position.y - range;
        if( start.x < 0 ) {
            start.x = 0;
        }
        if( start.y < 0 ) {
            start.y = 0;
        }
        
        end.x = position.x + range;
        if( end.x >= maxWidth ) {
            end.x = maxWidth - 1;
        }
        end.y = position.y + range;
        if( end.y >= maxHeight ) {
            end.y = maxHeight - 1;
        }
        boundingArea->first = start;
        boundingArea->second = end;
        setArea( boundingArea );
    } else {
        throw IllegalStateException( "Not valid position or movement provided" );
    }
}

void AreaIterator::setArea( std::pair<Point, Point> *area ) {
    this->area = area;
}

std::pair<Point,Point>* AreaIterator::getArea() {
    return area;
}

int AreaIterator::getCurrentPosition() {
    return currentPosition;
}

Point* AreaIterator::nextPosition() {
    Point start = area->first;
    Point end = area->second;
    
    int width = end.x - start.x;
    int height = end.y - start.y;
    
    Point offset( currentPosition / width, currentPosition % width );
    
    if( currentPosition < width * height ) {
        currentPosition++;
        return new Point( start.x + offset.x, start.y + offset.y );
    }
    return nullptr;
}

bool AreaIterator::hasNext() {
    if( hasCached ) {
        return true;
    }
    
    Point* position = nextPosition();
    if( position != nullptr ) {
        currentPosition++;
        hasCached = true;
        cached = *position;
        return true;
    }
    
    return false;
}

Point AreaIterator::next() {
    if ( hasCached ) {
        hasCached = false;
        return cached;
    }
    Point* position = nextPosition();
    if( position != nullptr ) {
        return *position;
    }

    //throw there's no next position exception
    return cached;
}
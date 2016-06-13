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
    delete area;
}

bool AreaIterator::isValid( Point& position ) {
    //All values are considered valid for the main iterator
    return true;
}

void AreaIterator::buildArea( Point& position,
                              int range, int maxWidth, int maxHeight ) {
    if( position.isValid( maxWidth , maxHeight ) && range > 0 ) {
        area = new std::pair<Point, Point>;
        Point start, end;
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
        area->first = start;
        area->second = end;
    } else {
        throw IllegalStateException( "Not valid position or range provided" );
    }
}

void AreaIterator::setArea( std::pair<Point, Point>* area ) {
    this->area = area;
}

std::pair<Point,Point>* AreaIterator::getArea() {
    return area;
}

int AreaIterator::getCurrentPosition() {
    return currentPosition;
}

void AreaIterator::setCurrentPosition( int currentPosition ) {
    this->currentPosition = currentPosition;
}

bool AreaIterator::nextPosition() {
    Point start = area->first;
    Point end = area->second;
    int width = end.x - start.x + 1;
    int height = end.y - start.y + 1;
    
    if( currentPosition < width * height ) {
        int offsetX = currentPosition % width;
        int offsetY = currentPosition / width;
        currentPosition++;
        cached.x = start.x + offsetX;
        cached.y = start.y + offsetY;
        return true;
    }
    return false;
}

bool AreaIterator::hasNext() {
    if( hasCached ) {
        return true;
    }
    
    if( nextPosition() ) {
        hasCached = true;
        return true;
    }
    
    return false;
}

const Point& AreaIterator::next() {
    if ( hasCached ) {
        hasCached = false;
        return cached;
    }

    if( nextPosition() ) {
        return cached;
    }

    Point start = area->first;
    Point end = area->second;
    int width = end.x - start.x + 1;
    int height = end.y - start.y + 1;
    throw EndOfIteratorException( currentPosition, width, height );
}
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
: currentPosition( 0 ), hasCached( false ), xOffset( 0 ), yOffset( 0 ) {

}

AreaIterator::AreaIterator( IteratorFilter* iteratorFilter )
: AreaIterator() {
    this->iteratorFilter = iteratorFilter;
}

AreaIterator::~AreaIterator() {

}

void AreaIterator::buildArea( Point position,
                             int range, int maxWidth, int maxHeight ) {
    std::pair<Point, Point>* boundingArea = new std::pair<Point, Point>();
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
    } else {
        throw IllegalStateException( "Not valid position or movement provided" );
    }
}

bool AreaIterator::hasNext() {
    if( hasCached ) {
        return true;
    }
    
    for ( int i = start.x + xOffset ;  i < end.x; xOffset ++ ) {
        for ( int j = start.y + yOffset ; j < end.y; yOffset++ ) {
            Point position = Point( start.x + xOffset, start.y + yOffset );
            if ( iteratorFilter->isValid( position ) ) {
                hasCached = true;
                cached = position;
                return true;
            }
        }
    }
    return false;
}

Point AreaIterator::next() {
    if ( hasCached ) {
        hasCached = false;
        return cached;
    }
    for ( int i = start.x + xOffset ;  i < end.x; i ++ ) {
        for ( int j = start.y + yOffset ; j < end.y; j++ ) {
            Point position = Point( start.x + xOffset, start.y + yOffset );
            if ( iteratorFilter->isValid( position ) ) {
                return position;
            }
        }
    }
    //throw there's no next position exception
    return cached;
}
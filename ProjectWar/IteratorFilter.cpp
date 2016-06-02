//
//  IteratorFilter.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 02/06/16.
//  Copyright (c) 2016 Alvaro Chambi Campos. All rights reserved.
//

#include "IteratorFilter.h"
#include "GameException.h"

IteratorFilter::IteratorFilter( Iterator* iterator )
: iterator( iterator ), nextSaved( false ) {

}

bool IteratorFilter::hasNext() {
    if( iterator->hasNext() ) {
        Point position = iterator->next();
        if( isValid( position ) ) {
            savedNext = position;
            nextSaved = true;
            return true;
        }
    }
    while( iterator->hasNext() ) {
        Point position = iterator->next();
        if( isValid( position ) ) {
            savedNext = position;
            nextSaved = true;
            return true;
        }
    }
    return false;
}

Point IteratorFilter::next() {
    if( nextSaved ) {
        nextSaved = false;
        return savedNext;
    }
    throw IllegalStateException(
    "Not available next position, call to hasNext() must be made before each next() call" );
}
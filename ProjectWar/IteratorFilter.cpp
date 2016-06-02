//
//  IteratorFilter.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 02/06/16.
//  Copyright (c) 2016 Alvaro Chambi Campos. All rights reserved.
//

#include "IteratorFilter.h"

IteratorFilter::IteratorFilter( Iterator* iterator )
: iterator( iterator ) {

}

bool IteratorFilter::hasNext() {
    if( iterator->hasNext() &&  isValid( iterator->next() ) ) {
        return true;
    }
    while ( iterator->hasNext() ) {
        if( isValid( iterator->next() ) ) {
            return true;
        }
    }
    return false;
}

Point IteratorFilter::next() {
    if( isValid( iterator->next() ) ) {
        return iterator->next();
    }
    while ( iterator->hasNext() ) {
        Point position = iterator->next();
        if( isValid( position ) ) {
            return position;
        }
    }
    //TODO: thow exception
    return iterator->next();
}
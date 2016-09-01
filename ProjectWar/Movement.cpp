//
//  Movement.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 22/4/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#include "Movement.h"

#include <algorithm>

static int NUM_MOVEMENTS = 0;

Movement::Movement() {
    std::cout <<        "Movements allocated: " << ++NUM_MOVEMENTS << std::endl;
}

Movement::Movement( int numActions ) {
    reserve( numActions );
    std::cout  <<       "Movements allocated: " << ++NUM_MOVEMENTS << std::endl;
}

Movement::~Movement() {
    actions.clear();
    std::cout  <<       "Movements dellocated: " << --NUM_MOVEMENTS << std::endl ;
}

void Movement::execute( MapContext& context ) {
    for ( Action* action : actions ) {
        action->execute( context );
    }
}

void Movement::cancel() {
    std::vector<Action*>::reverse_iterator reverseIterator = actions.rbegin();
    for ( ; reverseIterator!= actions.rend(); ++reverseIterator ) {
        (*reverseIterator)->cancel();
    }
}

void Movement::reserve( int numActions ) {
    actions.reserve( numActions );
}

const std::vector<Action*>& Movement::getActions() const {
    return actions;
}

bool Movement::contains( const Action& action ) const {
    for( Action* currentAction : actions ) {
        if( *currentAction == action ) {
            return true;
        }
    }
    return false;
}

//will not add the actions if there is already one that targets the same tile
bool Movement::addAction( Action& action ) {
    if( contains( action ) ) {
        return false;
    } else {
        actions.push_back( &action );
        return true;
    }
}
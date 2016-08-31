//
//  Movement.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 22/4/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#include "Movement.h"

#include <algorithm>

Movement::Movement() {
    
}

Movement::Movement( int numActions ) {
    reserve( numActions );
}

Movement::~Movement() {
    std::cout << "Dellocated Movement" << std::endl;
    for ( Action* action : actions ) {
        delete action;
    }
    actions.clear();
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
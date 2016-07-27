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

}

void Movement::execute() {
    for ( Action* action : actions ) {
        action->execute();
    }
}

void Movement::cancel() {
    for ( Action* action : actions ) {
        action->cancel();
    }
}

void Movement::reserve( int numActions ) {
    actions.reserve( numActions );
}

const std::vector<Action*>& Movement::getActions() const {
    return actions;
}

//will not add the actions if there is already one that targets the same tile
bool Movement::addAction( Action& action ) {
    //danger! danger! heavy operation!
    if( std::find(
            actions.begin(), actions.end(), &action ) != actions.end() ) {
        return false;
    } else {
        actions.push_back( &action );
        return true;
    }
}
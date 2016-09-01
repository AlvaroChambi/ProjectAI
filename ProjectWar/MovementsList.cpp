//
//  MovementsList.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 01/09/16.
//  Copyright (c) 2016 Alvaro Chambi Campos. All rights reserved.
//

#include "MovementsList.h"

MovementsList::MovementsList( std::vector<Action*>& actions )
: actions( actions ) {

}

MovementsList::~MovementsList() {
    //std::cout << "Dellocated moves list" << std::endl;
    for ( Option* movement : movements ) {
        delete movement;
    }
    
    for ( Action* action : actions ) {
        delete action;
    }
    
    movements.clear();
    actions.clear();
}

std::vector<Option*> MovementsList::getMovementsVector() const {
    return movements;
}

void MovementsList::reserve( int size ) {
    movements.reserve( size );
}

void MovementsList::addMovement( Movement& movement ) {
    movements.push_back( &movement );
}
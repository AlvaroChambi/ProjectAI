//
//  Action.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 01/06/16.
//  Copyright (c) 2016 Alvaro Chambi Campos. All rights reserved.
//

#include "Action.h"
#include "MoveCommand.h"

Action::Action() : moveCommand( nullptr ), command( nullptr ) {

}

Action::~Action() {
    
}

void Action::execute() {
    if( moveCommand != nullptr ) {
        moveCommand->execute();
    }
    if( command != nullptr ) {
        command->execute();
    }
}

void Action::cancel() {
    if( command != nullptr ) {
        command->execute();
    }
    if( moveCommand != nullptr ) {
        moveCommand->execute();
    }
}

bool Action::operator==( const Action& action ) const {
    if( moveCommand == nullptr || action.moveCommand == nullptr ) {
        return false;
    }
    if( *moveCommand == *action.moveCommand ) {
        return true;
    }
    return false;
}
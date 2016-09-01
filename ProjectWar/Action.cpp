//
//  Action.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 01/06/16.
//  Copyright (c) 2016 Alvaro Chambi Campos. All rights reserved.
//

#include "Action.h"
#include "MoveCommand.h"

Action::Action()
: moveCommand( nullptr ), command( nullptr ), score( NULL_SCORE ) {

}

Action::~Action() {
    
}

void Action::execute( MapContext& context ) {
    if( moveCommand != nullptr ) {
        moveCommand->execute( context );
    }
    if( command != nullptr ) {
        command->execute( context );
    }
}

void Action::cancel() {
    if( command != nullptr ) {
        command->cancel();
    }
    if( moveCommand != nullptr ) {
        moveCommand->cancel();
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

float Action::getValue( const Evaluator &evaluator,
                        const MapContext& context ) {
    if( score == NULL_SCORE ) {
        score = evaluator.getEvaluation( *this, context );
    }
    return score;
}
//
//  ActionBuilder.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 12/07/16.
//  Copyright (c) 2016 Alvaro Chambi Campos. All rights reserved.
//

#include "ActionBuilder.h"
#include "MoveCommand.h"
#include "AttackCommand.h"
#include "CaptureCommand.h"

MoveActionBuilder::MoveActionBuilder( const int unitID, const Point& destination )
: unitID( unitID ), destination( destination ) {
    
}

Action& MoveActionBuilder::createAction( MapContext &context ) const {
    Action* action = new Action();
    MoveCommand* moveCommand = new MoveCommand( context, unitID, destination );
    
    action->commands.push_back( moveCommand );
    
    return *action;
}

CaptureActionBuilder::CaptureActionBuilder( const int unitID,
                                            const Point& destination )
: unitID( unitID ), destination( destination ) {

}

Action& CaptureActionBuilder::createAction( MapContext &context ) const {
    Action* action = new Action();
    MoveCommand* moveCommand = new MoveCommand( context, unitID, destination );
    CaptureCommand* captureCommand = new CaptureCommand( context, unitID );
    
    action->commands.push_back( moveCommand );
    action->commands.push_back( captureCommand );
    
    return *action;
}

AttackActionBuilder::AttackActionBuilder( const int unitID, const int targetID,
                                          const Point& destination )
: unitID( unitID ), targetID( targetID ), destination( destination ) {
    
}

Action& AttackActionBuilder::createAction( MapContext &context ) const {
    Action* action = new Action();
    MoveCommand* moveCommand = new MoveCommand( context, unitID, destination );
    AttackCommand* attackCommand = new AttackCommand( context, unitID, targetID );
    
    action->commands.push_back( moveCommand );
    action->commands.push_back( attackCommand );
    return *action;
}
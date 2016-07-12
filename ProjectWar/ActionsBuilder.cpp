//
//  ActionsBuilder.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 12/7/16.
//  Copyright © 2016 Alvaro Chambi Campos. All rights reserved.
//

#include "ActionsBuilder.h"
#include "AreaIterator.h"
#include "MapContext.h"
#include "UnitFilter.h"
#include "AttackCommand.h"
#include "MoveCommand.h"
#include "CaptureCommand.h"

ActionsBuilder::ActionsBuilder( const int unitID,
                                            const Point& position )
: unitID( unitID ), position( position ) {

}

void ActionsBuilder::appendActions( const TargetTile &targetTile,
                                    MapContext &context,
                                    std::vector<Action *> &vector ) const {
    switch ( targetTile ) {
        case TARGET_ENTITY:
            createAppendAttackActions( context, vector );
            break;
        case TARGET_STRUCTURE:
            createAppendCaptureAction( context, vector );
            break;
        case TARGET_POSITION:
            createAppendMoveAction( context, vector );
            break;
        default:
            break;
    }
}

void ActionsBuilder::createAppendCaptureAction( MapContext &context,
                                        std::vector<Action *> &vector ) const {
    Action* action = new Action();
    MoveCommand* moveCommand = new MoveCommand( context, unitID, position );
    CaptureCommand* captureCommand = new CaptureCommand( context, unitID );
    
    action->commands.push_back( moveCommand );
    action->commands.push_back( captureCommand );
    
    vector.push_back( action );
}

void ActionsBuilder::createAppendMoveAction( MapContext &context,
                                        std::vector<Action *> &vector ) const {
    Action* action = new Action();
    MoveCommand* moveCommand = new MoveCommand( context, unitID, position );
    
    action->commands.push_back( moveCommand );
    
    vector.push_back( action );
}

void ActionsBuilder::createAppendAttackActions(
                MapContext &context, std::vector<Action*>& vector) const {
    
    Unit* unit = context.getEntity( unitID );
    Unit* entity = context.getEntity( position );
    
    AreaIterator areaIterator;
    areaIterator.buildArea( position, unit->getAttackRange(),
                    context.getNumColumns(), context.getNumRows() );
    UnitMovementFilter filter = UnitMovementFilter( areaIterator, context, *unit );
    while ( filter.hasNext() ) {
        const Point destination = filter.next();
        if( destination != position ) {
            Action* action = new Action();
            MoveCommand* moveCommand = new MoveCommand(
                                            context, unitID, destination );
            AttackCommand* attackCommand = new AttackCommand(
                                            context, unitID, entity->getId() );
            
            action->commands.push_back( moveCommand );
            action->commands.push_back( attackCommand );
            
            vector.push_back( action );
        }
    }
}
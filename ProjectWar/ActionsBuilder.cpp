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

void ActionsBuilder::appendActions( const TargetTile &targetTile,
                            MapContext &context,
                            const int unitID, const Point& position,
                            std::vector<Action *> &vector ) const {
    switch ( targetTile ) {
        case TARGET_ENTITY:
            createAppendAttackActions( context, unitID,
                                       position ,vector );
            break;
        case TARGET_STRUCTURE:
            createAppendCaptureAction( context, unitID,
                                       position, vector );
            createAppendMoveAction( context, unitID,
                                    position, vector );
            break;
        case TARGET_POSITION:
            createAppendMoveAction( context, unitID,
                                    position, vector );
            break;
        default:
            break;
    }
}

void ActionsBuilder::createAppendCaptureAction( MapContext &context,
                                const int unitID, const Point& position,
                                std::vector<Action *> &vector ) const {
    Action* action = new Action();
    MoveCommand* moveCommand = new MoveCommand( unitID, position );
    CaptureCommand* captureCommand = new CaptureCommand( unitID );
    
    action->moveCommand = moveCommand;
    action->command = captureCommand;
    
    vector.push_back( action );
}

void ActionsBuilder::createAppendMoveAction( MapContext &context,
                                const int unitID, const Point& position,
                                std::vector<Action *> &vector ) const {
    Action* action = new Action();
    MoveCommand* moveCommand = new MoveCommand( unitID, position );
    
    action->moveCommand = moveCommand;
    
    vector.push_back( action );
}

void ActionsBuilder::createAppendAttackActions( MapContext &context,
                                const int unitID, const Point& position,
                                std::vector<Action*>& vector) const {
    
    Unit* unit = context.getEntity( unitID );
    Unit* entity = context.getEntity( position );
    
    if( unit->getPosition() == entity->getPosition() ) {
        throw IllegalStateException( "No allowed more than one unit in the same position" );
    }
    
    AreaIterator areaIterator;
    areaIterator.buildArea( position, unit->getAttackRange(),
                    context.getNumColumns(), context.getNumRows() );
    UnitMovementFilter filter = UnitMovementFilter( areaIterator, context,
                                                    *unit );
    while ( filter.hasNext() ) {
        const Point destination = filter.next();
        if( entity->getPosition().onRange( destination,
                                           unit->getAttackRange() ) ) {
            Action* action = new Action();
            MoveCommand* moveCommand = new MoveCommand( unitID,
                                                        destination );
            AttackCommand* attackCommand = new AttackCommand( unitID,
                                                              entity->getId() );
            
            action->moveCommand = moveCommand;
            action->command = attackCommand;
            
            vector.push_back( action );
        }
    }
}
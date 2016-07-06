//
//  MovesBuilder.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 06/07/16.
//  Copyright (c) 2016 Alvaro Chambi Campos. All rights reserved.
//

#include "MovesBuilder.h"
#include "AreaIterator.h"
#include "AttackCommand.h"
#include "MoveCommand.h"
#include "CaptureCommand.h"

MovesBuilder::MovesBuilder( const Map& map ) : map( map ) {

}

void MovesBuilder::buildActions( int playerID, int numActions ) {
    int numUnits = 0;
    actions.reserve( numUnits );
}

// reserve actions vector and iterate over the valid area
void MovesBuilder::buildUnitActions( int unitID, int playerID,
                                     int numActions ) {
    Unit* unit = map.getEntity( unitID );
    
    int maxAllowedActions = ( unit->getMovement() * 4 ) * 2;
    std::vector<Action*> unitActions( maxAllowedActions );
    
    int explorationRange = unit->getMovement() + unit->getAttackRange();
    AreaIterator areaIterator;
    areaIterator.buildArea( unit->getPosition(), explorationRange,
                            map.getNumColumns(), map.getNumRows() );
    while( areaIterator.hasNext() ) {
        const Point destination = areaIterator.next();
        if( unit->getPosition().onRange( destination, explorationRange ) ) {
            // return action builder
            resolveActions( *unit, playerID, destination, actions );
            
            //builder.append( actions )
        }
    }
    
    //actions sort
}

// resolve the action needed to build for the given destination
void MovesBuilder::resolveActions( const Unit& unit, int playerID,
                                   const Point& destination,
                                  std::vector<Action*>& actions ) {
    Unit* entity = map.getEntity( destination );
    Building* structure = map.getStructure( destination );
    
    if( entity != nullptr && entity->getId() != playerID ) {
        appendAttackActions( unit, *entity, actions );
    } else if( map.isValidPosition( destination )
              && entity->getPosition().onRange( destination, unit.getMovement()) ) {
        if ( structure != nullptr && !structure->isCaptured( playerID ) ) {
            appendCaptureAction( unit, *structure, actions );
        } else {
            appendMoveAction( unit, actions );
        }
    }
}

// append attacks actions available for the given position
void MovesBuilder::appendAttackActions( const Unit& unit, const Unit& target,
                                        std::vector<Action*>& actions ) {
    AreaIterator areaIterator;
    areaIterator.buildArea( target.getPosition(), unit.getAttackRange(),
                            map.getNumColumns(), map.getNumRows() );
    while ( areaIterator.hasNext() ) {
        const Point destination = areaIterator.next();
        if( unit.getPosition().onRange( destination, unit.getMovement() ) ) {
            // create move command
            // create attack command
            
            // create and add Action( move, attack, score )
        }
    }
}

// append capture actions available for the given position
void MovesBuilder::appendCaptureAction( const Unit& unit, const Building& structure,
                                        std::vector<Action*>& actions ) {
    // create move command
    // create attack commmand
    
    // create and add Action( move, capture, score )
}

// append move actions available for the given position
void MovesBuilder::appendMoveAction( const Unit& unit,
                                     std::vector<Action*>& actions ) {
    // create move command
    
    // create and add Action( move, score )
}
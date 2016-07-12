//
//  ActionsProvider.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 10/7/16.
//  Copyright © 2016 Alvaro Chambi Campos. All rights reserved.
//

#include "ActionsProvider.h"
#include "AreaIterator.h"
#include "Option.h"

ActionsProvider::ActionsProvider( MapContext& mapContext )
: mapContext( mapContext ) {

}

std::vector<Option*> ActionsProvider::generateMovements(
                                    int playerID, int numActions ) const {
    std::vector<Option*>* options = new std::vector<Option*>;
    return *options;
}

void ActionsProvider::buildActions( int playerID, int numActions ) {
    int numUnits = 0;
    actions.reserve( numUnits * numActions );
}

// iterate over the unit valid area and append (numActions) unit actions
// to the actions vector
std::vector<Action*>& ActionsProvider::buildUnitActions( int unitID, int playerID,
                                        int numActions ) {
    Unit* unit = mapContext.getEntity( unitID );
    
    int maxAllowedActions = ( unit->getMovement() * 4 ) * 2;
    //ActionBuilder* actionBuilder = new ActionBuilder( maxAllowedActions );
    std::vector<Action*>* actions = new std::vector<Action*>( maxAllowedActions );
    
    int explorationRange = unit->getMovement() + unit->getAttackRange();
    AreaIterator areaIterator;
    areaIterator.buildArea( unit->getPosition(), explorationRange,
                            mapContext.getNumColumns(), mapContext.getNumRows() );
    while( areaIterator.hasNext() ) {
        const Point destination = areaIterator.next();
        if( unit->getPosition().onRange( destination, explorationRange ) ) {

            resolveActions( *unit, playerID, destination, *actions );
        }
    }
    return *actions;
}

void ActionsProvider::appendUnitActions( std::vector<Action *> actions,
                                         int numActions ) {
    //sort actions
        //std::sort( actions )
    //this->actions.append( (actions)0 - numActions )
}

ActionBuilder& ActionsProvider::createActionBuilder(
                                            const Unit& unit, int playerID,
                                            const Point& destination  ) {
    
    Unit* entity = mapContext.getEntity( destination );
    Building* structure = mapContext.getStructure( destination );
    
    if( entity != nullptr && entity->getId() != playerID ) {
        appendAttackActions( unit, *entity, actions );
    } else if( mapContext.isValidPosition( destination )
              && entity->getPosition().onRange( destination, unit.getMovement()) ) {
        if ( structure != nullptr && !structure->isCaptured( playerID ) ) {
            appendCaptureAction( unit, *structure, actions );
        } else {
            appendMoveAction( unit, actions );
        }
    }

}

// resolve the action needed to build for the given destination
void ActionsProvider::resolveActions( const Unit& unit, int playerID,
                                      const Point& destination,
                                  std::vector<Action*>& actions ) {
    Unit* entity = mapContext.getEntity( destination );
    Building* structure = mapContext.getStructure( destination );
    
    if( entity != nullptr && entity->getId() != playerID ) {
        appendAttackActions( unit, *entity, actions );
    } else if( mapContext.isValidPosition( destination )
              && entity->getPosition().onRange( destination, unit.getMovement()) ) {
        if ( structure != nullptr && !structure->isCaptured( playerID ) ) {
            appendCaptureAction( unit, *structure, actions );
        } else {
            appendMoveAction( unit, actions );
        }
    }
}

// append attacks actions available for the given position
void ActionsProvider::appendAttackActions( const Unit& unit, const Unit& target,
                                           std::vector<Action*>& actions ) {
    AreaIterator areaIterator;
    areaIterator.buildArea( target.getPosition(), unit.getAttackRange(),
                           mapContext.getNumColumns(), mapContext.getNumRows() );
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
void ActionsProvider::appendCaptureAction( const Unit& unit,
                                           const Building& structure,
                                           std::vector<Action*>& actions ) {
    // create move command
    // create attack commmand
    
    // create and add Action( move, capture, score )
}

// append move actions available for the given position
void ActionsProvider::appendMoveAction( const Unit& unit,
                                        std::vector<Action*>& actions ) {
    // create move command
    
    // create and add Action( move, score )
}
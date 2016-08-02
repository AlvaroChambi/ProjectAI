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
#include "Player.h"
#include "GameException.h"
#include "ActionEvaluator.h"

#include <cmath>

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
    
    //for each unit
        //actions - buildUnitActions;
        //filter actions if needed
    
    //result {unit<0,n>...unitN<0,n>}
    
    //getVariations: {<0,0>,<0,1>,<1,0>,<1,1>}
    
    //mapVariations: movements = vector<Movement>
    
    //return movements
}

void ActionsProvider::sortActions( std::vector<Action *>& actions,
                                   const Evaluator& evaluator ) const {
    std::sort( actions.begin(), actions.end(),
                                    Compare( evaluator, mapContext ) );
}

std::vector<Action*>& ActionsProvider::buildUnitActions( int unitID ) {
    Unit* unit = mapContext.getEntity( unitID );
    
    int maxAllowedActions = ( unit->getMovement() * 4 ) * 2;
    std::vector<Action*>* actions = new std::vector<Action*>( maxAllowedActions );
    
    int explorationRange = unit->getMovement() + unit->getAttackRange();
    AreaIterator areaIterator;
    areaIterator.buildArea( unit->getPosition(), explorationRange,
                            mapContext.getNumColumns(), mapContext.getNumRows() );
    while( areaIterator.hasNext() ) {
        const Point destination = areaIterator.next();
        if( unit->getPosition().onRange( destination, explorationRange ) ) {
            TargetTile targetTile = getTargetTileForPosition( unit->getId(),
                                                              destination );
            if( targetTile != TARGET_NOT_AVAILABLE ) {
                actionsBuilder.appendActions( targetTile, mapContext, unitID,
                                              destination, *actions );
            }
        }
    }
    return *actions;
}

TargetTile ActionsProvider::getTargetTileForPosition( const int unitID,
                                                      const Point& position ) {
    Unit* unit = mapContext.getEntity( unitID );
    Unit* entity = mapContext.getEntity( position );
    Building* structure = mapContext.getStructure( position );
    
    if( entity != nullptr && entity->getOwnerID() != unit->getOwnerID() ) {
        return TARGET_ENTITY;
    } else if( unit->getPosition().onRange( position, unit->getMovement()) ) {
        if ( structure != nullptr && !structure->isCaptured( unit->getOwnerID() ) ) {
            return TARGET_STRUCTURE;
        } else if( entity != nullptr ) {
            if( entity->getId() == unit->getId() ) {
                return TARGET_POSITION;
            }
        } else {
            return TARGET_POSITION;
        }
    }
    
    return TARGET_NOT_AVAILABLE;
}

std::vector<Movement*>& ActionsProvider::mapVariations(
                        const int numUnits,
                        std::vector<std::vector<int>>& variations,
                        std::vector<Action*>& actions ) {
    std::vector<Movement*>* movements = new std::vector<Movement*>();
    movements->reserve( (int)variations.size() );
    
    if( variations.empty() && actions.empty() ) {
        return *movements;
    }
    
    if( actions.size() != variations.at( 0 ).size() * numUnits ) {
        throw IllegalStateException( "Params not valid" );
    }
    
    for ( int i = 0; i < variations.size(); i++ ) {
        std::vector<int> actionIDs = variations.at( i );
        int numActions = (int)actionIDs.size();
        Movement* movement = new Movement( numActions );
        for ( int j = 0; j < actionIDs.size(); j++ ) {
            int actionID = actionIDs.at( j );
            int key = actionID + j*numActions;
            movement->addAction( *actions[key] );
        }
        movements->push_back( movement );
    }
    
    return *movements;
}
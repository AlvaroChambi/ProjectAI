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
    
    if( entity != nullptr && entity->getId() != unit->getOwnerID() ) {
        return TARGET_ENTITY;
    } else if( mapContext.isValidPosition( position )
              && entity->getPosition().onRange( position, unit->getMovement()) ) {
        if ( structure != nullptr && !structure->isCaptured( unit->getOwnerID() ) ) {
            return TARGET_STRUCTURE;
        } else {
            return TARGET_POSITION;
        }
    }
    return TARGET_NOT_AVAILABLE;
}
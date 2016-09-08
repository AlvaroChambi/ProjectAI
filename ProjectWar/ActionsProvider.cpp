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

#ifdef _WIN32
#include <algorithm>
#endif

std::unordered_map<int, std::vector<std::vector<int>>> ActionsProvider::variations;



ActionsProvider::ActionsProvider( MapContext& mapContext )
: mapContext( mapContext ) {

}

void ActionsProvider::init() {
    for ( int i = 1; i <= 3; i++ ) {
        std::vector<std::vector<int>>* v = new std::vector<std::vector<int>>;
        v->reserve(4);
        std::vector<int> variation(i);
        generateVariations(v, 4, variation, 0);
        variations[i] = *v;
        delete v;
    }
}

MovementsList& ActionsProvider::generateMovements(
                                    int playerID, int numActions ) const {
    const Evaluator& evaluator = ActionEvaluator();
    std::vector<Action*>* actionsSet = new std::vector<Action*>;
    
    const Player* player = mapContext.getPlayer( playerID );
    
    std::vector<Unit*> army = player->getUnits();
    int numUnits = (int)army.size();
    actionsSet->reserve( numUnits );
    
    for ( const Unit* unit : army ) {
        std::vector<Action*>& unitActions = buildUnitActions( unit->getId() );
        sortActions( unitActions, evaluator );
        actionsSet->insert( actionsSet->end(),
                           unitActions.begin(), unitActions.begin() + numActions );
        
        std::vector<Action*> unusedActions;
        unusedActions.insert( unusedActions.end(), unitActions.begin() + numActions,
                              unitActions.end() );
        unitActions.clear();
        delete &unitActions;
        for ( Action* action : unusedActions ) {
            delete action;
        }
    }
    
    std::vector<std::vector<int>> variations = generateVariations( numActions,
                                                                   numUnits );
    
    MovementsList& movements = mapVariations( numActions, variations,
                                                     *actionsSet );
    
    return movements;
}

void ActionsProvider::sortActions( std::vector<Action *>& actions,
                                   const Evaluator& evaluator ) const {
    std::sort( actions.begin(), actions.end(),
                                    Compare( evaluator, mapContext ) );
}

std::vector<Action*>& ActionsProvider::buildUnitActions( int unitID ) const {
    Unit* unit = mapContext.getEntity( unitID );
    
    int maxAllowedActions = ( unit->getMovement() * 4 ) * 2;
    std::vector<Action*>* actions = new std::vector<Action*>();
    actions->reserve( maxAllowedActions );
    
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
                                                      const Point& position ) const {
    Unit* unit = mapContext.getEntity( unitID );
    Unit* entity = mapContext.getEntity( position );
    Building* structure = mapContext.getStructure( position );
    
    if( unit == entity ) {
        return TARGET_POSITION;
    }

    if( entity != nullptr  ) {
        if( entity->getOwnerID() != unit->getOwnerID() ) {
            return TARGET_ENTITY;
        } else {
            return TARGET_NOT_AVAILABLE;
        }
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

MovementsList& ActionsProvider::mapVariations(
                        const int numActions,
                        std::vector<std::vector<int>>& variations,
                        std::vector<Action*>& actions ) const {
    MovementsList* movementsList = new MovementsList( actions );
    movementsList->reserve( (int)variations.size() );
    
    if( variations.empty() && actions.empty() ) {
        return *movementsList;
    }
    
    if( actions.size() < variations.at( 0 ).size() * numActions ) {
        throw IllegalStateException( "Params not valid" );
    }
    
    for ( int i = 0; i < variations.size(); i++ ) {
        std::vector<int> actionIDs = variations.at( i );
        int numUnits = (int)actionIDs.size();
        Movement* movement = new Movement( numUnits );
        for ( int j = 0; j < actionIDs.size(); j++ ) {
            int actionID = actionIDs.at( j );
            int key = actionID + j*numActions;
            movement->addAction( *actions[key] );
        }
        movementsList->addMovement( *movement );
    }
    
    return *movementsList;
}

std::vector<std::vector<int>>& ActionsProvider::generateVariations(
                                         int numActions, int numUnits ) const {
	// look for a pre-calculated variation, if it doesn´t exist, create a new one
	auto iterator = ActionsProvider::variations.find(numUnits);
	if ( iterator != ActionsProvider::variations.end() ) {
		return iterator->second;
	} else {
		std::vector<std::vector<int>>* v = new std::vector<std::vector<int>>;
		v->reserve(numActions);
		std::vector<int> variation(numUnits);
		generateVariations(v, numActions, variation, 0);
		ActionsProvider::variations[numUnits] = *v;
		return ActionsProvider::variations[numUnits];
	}
}

void ActionsProvider::generateVariations( std::vector<std::vector<int>> *sequence,
                         int numElements, std::vector<int> variation,
                         int count ) {
    if( count < variation.size() ){
        for( int i = 0; i < numElements; i++ ) {
            variation[count] = i;
            generateVariations( sequence, numElements, variation, count+1 );
        }
    }else{
        sequence->push_back( variation );
    }
}
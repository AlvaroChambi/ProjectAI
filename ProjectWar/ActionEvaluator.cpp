//
//  ActionEvaluator.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 28/07/16.
//  Copyright (c) 2016 Alvaro Chambi Campos. All rights reserved.
//

#include "ActionEvaluator.h"
#include "MoveCommand.h"
#include "Player.h"

//will evaluate if the action is worth been explored
float ActionEvaluator::getEvaluation( const Action& action,
                                     const MapContext& context ) const {
    
    // capture and attack actions are considered to have enough impact the be evaluated if there is one of them so we set a high score
    float captureAttackModifier = 0;

    if ( action.command != nullptr ) {
        captureAttackModifier = 1;
    }

    //influence for position
    const Point& destination = action.moveCommand->getDestination();
    
    float positionInfluence = evaluateValues(
            getHeadquarterInfluence( destination, context ),
            getOpponentsInfluence( destination, context ),
            getAlliesInfluence( destination, context ),
            getOpponentsInfluence( destination, context ) );
    
    return positionInfluence + captureAttackModifier;
}

float ActionEvaluator::evaluateValues( const float headquarterInfluence,
                                    const float enemyHeadquarterInfluence,
                                    const float alliesInfluence,
                                    const float opponentsInfluence ) const {
    float result = 1/headquarterInfluence + 1/enemyHeadquarterInfluence
                    + 1/alliesInfluence - 1/opponentsInfluence;
    return result;
}

float ActionEvaluator::getHeadquarterInfluence( const Point &position,
                                        const MapContext &context ) const {
    // + if i get closer to my base
    // get distance to my headquarter
    Building* headquarter = context.getPlayer().getHeadquarter();
    return headquarter->getPosition().distance( position );
}

float ActionEvaluator::getOpponentHeadquarterInfluence(
                                        const Point &position,
                                        const MapContext &context ) const {
    // + if i get closer to the enemy base
    // get distance to the enemy base
    Building* headquarter = context.getOpponent().getHeadquarter();
    return headquarter->getPosition().distance( position );
}

float ActionEvaluator::getAlliesInfluence( const Point &destination,
                                        const MapContext &context ) const {
    // + if i have friendly units closer
    // iterate friendly units and calculate distance
    float alliesDistance = 0;
    std::vector<int> allies = context.getPlayer().getUnitsReference();
    for( int unitReference : allies ) {
        Point position = context.getEntityReference( unitReference );
        alliesDistance += position.distance( destination );
    }
    return alliesDistance / allies.size();
}

float ActionEvaluator::getOpponentsInfluence( const Point &destination,
                                        const MapContext &context ) const {
    // - if i have enemy units closer
    // iterate enemy units and calculate distance
    float opponentsDistance = 0;
    std::vector<int> opponents = context.getOpponent().getUnitsReference();
    for( int unitReference : opponents ) {
        Point position = context.getEntityReference( unitReference );
        opponentsDistance += position.distance( destination );
    }
    return opponentsDistance / opponents.size();
}
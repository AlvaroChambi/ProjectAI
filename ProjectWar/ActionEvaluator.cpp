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
    float headquaterWight = 0, opponentHeadquarterWeight = 0, alliesWeight = 0, opponentsWeight = 0;
    if( headquarterInfluence != 0 ) {
        headquaterWight = 1/headquarterInfluence;
    }
    if( enemyHeadquarterInfluence != 0 ){
        opponentHeadquarterWeight = 1/enemyHeadquarterInfluence;
    }
    if( alliesInfluence != 0 ) {
        alliesWeight = 1/alliesInfluence;
    }
    if ( opponentsInfluence != 0 ) {
        opponentsWeight = 1/opponentsInfluence;
    }
    
    float result = headquaterWight + opponentHeadquarterWeight
                    + alliesWeight - opponentsWeight;
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
    std::vector<Unit*> allies = context.getPlayer().getUnits();
    for( const Unit* unit : allies ) {
        Point position = unit->getPosition();
        alliesDistance += position.distance( destination );
    }
    return alliesDistance / allies.size();
}

float ActionEvaluator::getOpponentsInfluence( const Point &destination,
                                        const MapContext &context ) const {
    // - if i have enemy units closer
    // iterate enemy units and calculate distance
    float opponentsDistance = 0;
    std::vector<Unit*> opponents = context.getOpponent().getUnits();
    for( const Unit* unit : opponents ) {
        Point position = unit->getPosition();
        opponentsDistance += position.distance( destination );
    }
    return opponentsDistance / opponents.size();
}
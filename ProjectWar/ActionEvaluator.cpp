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
    
    Unit* actor = context.getEntity( action.moveCommand->getUnitID() );

    //influence for position
    const Point& destination = action.moveCommand->getDestination();
    
    float positionInfluence = defendHeadquarterInfluence( destination, context ) +
        canCoverAllyInfluence( *actor, destination, context );
    
    return positionInfluence + captureAttackModifier;
}

float ActionEvaluator::defendHeadquarterInfluence( const Point &position,
                                                const MapContext &context ) const {
    
    Building* headquarter = context.getPlayer().getHeadquarter();
    if( position == headquarter->getPosition() ) {
        std::vector<Unit*> opponents = context.getOpponent().getUnits();
        
        float influence = 0;
        float modifier = 0.1;
        
        for( const Unit* unit : opponents ) {
            Point position = unit->getPosition();
            if( position.onRange( headquarter->getPosition(), unit->getMovement() ) ) {
                influence += modifier;
            }
        }
        return influence;
    }

    return 0;
}

float ActionEvaluator::canCoverAllyInfluence( const Unit& actor,
                                              const Point &destination,
                                        const MapContext &context ) const {
    std::vector<Unit*> allies = context.getPlayer().getUnits();
    
    float influence = 0;
    float modifier = 0.1;
    
    for( const Unit* unit : allies ) {
        Point position = unit->getPosition();
        if( destination.onRange( position, actor.getMovement() ) ) {
            influence += modifier;
        }
    }
    return influence;
}
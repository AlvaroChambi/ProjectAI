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
int ActionEvaluator::getEvaluation( const Action& action,
                                    const MapContext& context ) {
    // capture and attack actions are considered to have enough impact the be evaluated if there is one of them
    if ( action.command != nullptr ) {
        //max score?
    }

    const Point& destination = action.moveCommand->getDestination();
    // + if i get closer to any building
        // iterate buildings and calculate distance
        //TODO: future user story
    
    // + if i get closer to my base
        // get distance to my headquarter
    Building* headquarter = context.getPlayer().getHeadquarter();
    int headquarterDistance = headquarter->getPosition()
                                        .distance( destination );
    
    // + if i get closer to the enemy base
        // get distance to the enemy base
    Building* enemyHeadquarter = context.getOpponent().getHeadquarter();
    int enemyHeadquarterDistance = enemyHeadquarter->getPosition()
                                                .distance( destination );
    // + if i have friendly units closer
        // iterate friendly units and calculate distance
    int alliesDistance = 0;
    std::vector<int> allies = context.getPlayer().getUnitsReference();
    for( int unitReference : allies ) {
        Point position = context.getEntityReference( unitReference );
        alliesDistance += destination.distance( position );
    }
    
    // - if i have enemy units closer
        // iterate enemy units and calculate distance
    int opponentsDistance = 0;
    std::vector<int> opponents = context.getPlayer().getUnitsReference();
    for( int unitReference : opponents ) {
        Point position = context.getEntityReference( unitReference );
        opponentsDistance += destination.distance( position );
    }
    
    
    return 0;
}

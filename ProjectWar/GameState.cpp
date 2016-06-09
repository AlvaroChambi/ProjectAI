
//
//  GameState.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 30/5/16.
//  Copyright © 2016 Alvaro Chambi Campos. All rights reserved.
//

#include "GameState.h"
#include "GameException.h"
#include "MoveCommand.h"
#include "AttackCommand.h"
#include "CaptureCommand.h"
#include "HeuristicFunction.h"
#include "AreaIterator.h"
#include "UnitFilter.h"
#include "Movement.h"

const int GameState::WIN_VALUE;
const int GameState::LOST_VALUE;
const int GameState::NOT_FINISHED;
const int TACTIC_POSSIBILITIES = 2;

GameState::GameState( IPlayer* const player, IPlayer* const enemy,
                      IMap* map )
: player( player ), enemy( enemy ), map( map ){

}

GameState::~GameState() {

}

IPlayer* const GameState::getPlayer() {
    return player;
}

IPlayer* const GameState::getEnemy() {
    return enemy;
}

int GameState::getGameOverScore() {
    int gameScore = GameState::NOT_FINISHED;
    bool playerHasCapturedHQ = player->hasCapturedHQ( (Player*)enemy );
    bool enemyHasCapturedHQ = enemy->hasCapturedHQ( (Player*)player );
    
    bool playerHasUnitAlive = player->hasUnitAlive();
    bool enemyHasUnitAlive = enemy->hasUnitAlive();
    
    if ( playerHasCapturedHQ && enemyHasCapturedHQ ) {
        throw IllegalStateException( "both captured at the same time" );
    } else if ( !playerHasUnitAlive && !enemyHasUnitAlive ) {
        throw IllegalStateException( "HQ captured without units" );
    } else {
        if( !playerHasUnitAlive || enemyHasCapturedHQ ) {
            return gameScore = GameState::LOST_VALUE;
        }else if( !enemyHasUnitAlive || playerHasCapturedHQ ) {
            return gameScore = GameState::WIN_VALUE;
        }
    }
    
    return gameScore;
}

std::vector<Option*>* GameState::getMovesList( Player* player,
                                               Player* opponent ) {
    std::vector<std::vector<Action*>*>* unitsActions =
        new std::vector<std::vector<Action*>*>;
    
    invalidatedPositions.clear();
    for ( Unit* unit : player->getAliveUnits() ) {
        std::vector<Action*>* unitActions =
            filterUnitActions( unit , player, opponent, TACTIC_POSSIBILITIES );
        unitsActions->push_back( unitActions );
    }
    
    return &buildMovesList( (int)player->getAliveUnits().size(), *unitsActions );
}

std::vector<Action*>* GameState::filterUnitActions( Unit *unit,
                                                    Player* player,
                                                    Player* opponent,
                                                    int numActions ) {
    Map* map = (Map*)this->map;
    int addedActions = 0;
    std::vector<Action*>* actions = new std::vector<Action*>();
    
    std::vector<Action*>* capture =
        unit->getCaptureActions( map, player, map->getBuildings(), *this );
    if( !capture->empty() &&
        capture->size() <= numActions ) {
        actions->insert( actions->end(), capture->begin(), capture->end() );
        addedActions = (int)capture->size();
        
        if( addedActions == numActions ) {
            return actions;
        }
    }
    
    std::vector<Action*>* attack =
        unit->getAttackActions( map, opponent->getAliveUnits(), *this );
    
    if ( !attack->empty()
         && (attack->size() + addedActions) <=  numActions ) {
        actions->insert( actions->end(), attack->begin(), attack->end() );
        addedActions += attack->size();
        
        if( addedActions == numActions ) {
            return actions;
        }
    }
    
    std::vector<Point>& destinations = getBestUnitDestination(
                                        map->getBuildings().at(0), unit );
    
    int pos = 0;
    for ( int i = addedActions; i < numActions; i++ ) {
        Action* action = new Action;
        MoveCommand* command = new MoveCommand( unit, map, destinations.at( pos ) );
        invalidatedPositions.push_back( destinations.at( pos ) );
        action->commands.push_back( command );
        actions->push_back( action );
        pos++;
    }
    
    return actions;
}

std::vector<Point>& GameState::getBestUnitDestination( Building *headquarter,
                                                      Unit *unit ) {
    std::vector<Point>* result = new std::vector<Point>;
    std::vector<Point>* preferedActions = new std::vector<Point>;
    std::vector<Point>* actions = new std::vector<Point>;
    
    AreaIterator* areaIterator = new AreaIterator();
    areaIterator->buildArea( unit->getPosition() , unit->getMovement(),
                            MAP_WIDTH, MAP_HEIGHT );
    Iterator* unitMoveIterator = new UnitMovementFilter( areaIterator,
                                                        (Map*)map, unit );
    while ( unitMoveIterator->hasNext() ) {
        //TODO: Implement as a filter
        Point destination = unitMoveIterator->next();
        if( !isInvalidated( destination ) ) {
            Point start = unit->getPosition();
            Point end = headquarter->getPosition();
            int distance = start.distance( end );
            int newDistance = destination.distance( end );
            
            if( newDistance < distance ) {
                preferedActions->push_back( destination );
            } else {
                actions->push_back( destination );
            }
        }
    }
    
    result->insert( result->end(), preferedActions->begin(),
                   preferedActions->end() );
    result->insert( result->end(), actions->begin(), actions->end() );
    
    if( result->size() < 4 ) {
        throw IllegalStateException( "Not enough destinations provided" );
    }
    
    return *result;
}

std::vector<Action*>* GameState::getBestUnitMoves( Building *headquarter,
                                                   Unit* unit ) {
    std::vector<Action*>* result = new std::vector<Action*>;
    std::vector<Action*>* preferedActions = new std::vector<Action*>;
    std::vector<Action*>* actions = new std::vector<Action*>;
    
    AreaIterator* areaIterator = new AreaIterator();
    areaIterator->buildArea( unit->getPosition() , unit->getMovement(),
                            MAP_WIDTH, MAP_HEIGHT );
    Iterator* unitMoveIterator = new UnitMovementFilter( areaIterator,
                                                        (Map*)map, unit );
    while ( unitMoveIterator->hasNext() ) {
        //TODO: Implement as a filter
        Point destination = unitMoveIterator->next();
        if( !isInvalidated( destination ) ) {
            Point start = unit->getPosition();
            Point end = headquarter->getPosition();
            int distance = start.distance( end );
            int newDistance = destination.distance( end );
            
            MoveCommand* move = new MoveCommand( unit, map,
                                                 destination );
            Action* action = new Action;
            action->commands.push_back( move );
            if( newDistance < distance ) {
                preferedActions->push_back( action );
            } else {
                actions->push_back( action );
            }
        }
    }
    
    result->insert( result->end(), preferedActions->begin(),
                    preferedActions->end() );
    result->insert( result->end(), actions->begin(), actions->end() );
    return result;
}

void GameState::generateTacticSequence( std::vector<std::vector<int>> *sequence,
                                       int numElements, std::vector<int> variation,
                                       int count ) {
    if( count < variation.size() ){
        for( int i = 0; i < numElements; i++ ) {
            variation[count] = i;
            generateTacticSequence( sequence, numElements, variation, count+1 );
        }
    }else{
        sequence->push_back( variation );
        
    }
}

std::vector<Option*>& GameState::buildMovesList(
                                int numUnits,
                                std::vector<std::vector<Action*>*>& actions ) {
    if( !actions.empty() ) {
        std::vector<Option*>* options = new std::vector<Option*>;
        std::vector<std::vector<int>> tacticMovements;
        std::vector<int> variation( numUnits );
        generateTacticSequence( &tacticMovements, TACTIC_POSSIBILITIES, variation, 0 );
        
        for( std::vector<int> sentence : tacticMovements ) {
            Movement* movement = new Movement;
            for( int i = 0; i < numUnits; i++ ) {
                Action* action = actions.at( i )->at( sentence.at( i ) );
                movement->actions.push_back( action );
            }
            options->push_back( movement );
        }
        
        return *options;
    }
    throw IllegalStateException( "Not legal actions provided" );
}

bool GameState::isInvalidated( Point position ) {
    bool invalidated =
    std::find( invalidatedPositions.begin(),
              invalidatedPositions.end(),
              position) != invalidatedPositions.end();

    return invalidated;
}

void GameState::addToInvalidated( Point position ) {
    invalidatedPositions.push_back( position );
}
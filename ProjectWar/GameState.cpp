
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
const int TACTIC_POSSIBILITIES = 4;

GameState::GameState( IPlayer* const player, IPlayer* const enemy,
                      IMap* map )
: player( player ), enemy( enemy ), map( map ) {

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
    std::vector<Unit*> units = player->getUnits();
    for ( Unit* unit : units ) {
        std::vector<Action*>* unitActions =
            filterUnitActions( unit , player, opponent, TACTIC_POSSIBILITIES );
        unitsActions->push_back( unitActions );
    }
    
    return &buildMovesList( (int)units.size(), *unitsActions );
}

std::vector<Action*>* GameState::filterUnitActions( Unit *unit,
                                                    Player* player,
                                                    Player* opponent,
                                                    int numActions ) {
    Map* map = (Map*)this->map;
    int addedActions = 0;
    std::vector<Action*>* actions = new std::vector<Action*>();
    
    std::vector<Action*>* capture =
        unit->getCaptureActions( map, player, map->getStructures(), *this );
    if( !capture->empty() &&
        capture->size() <= numActions ) {
        actions->insert( actions->end(), capture->begin(), capture->end() );
        addedActions = (int)capture->size();
        
        if( addedActions == numActions ) {
            return actions;
        }
    }
    
    std::vector<Action*>* attack =
        unit->getAttackActions( map, opponent->getUnits(), *this );
    
    if ( !attack->empty()
         && (attack->size() + addedActions) <=  numActions ) {
        actions->insert( actions->end(), attack->begin(), attack->end() );
        addedActions += attack->size();
        
        if( addedActions == numActions ) {
            return actions;
        }
    }
    
    std::vector<Point>* destinations = getBestUnitDestination(
                                        *player->getHeadquarter(),
                                        *opponent->getHeadquarter(), *unit );
    
    int pos = 0;
    for ( int i = addedActions; i < numActions; i++ ) {
        if( destinations->size() > pos ) {
            if( !isInvalidated( destinations->at( pos ) ) ) {
                invalidatedPositions.push_back( destinations->at( pos ) );
                Action* action = new Action;
                MoveCommand* command =
                new MoveCommand( *unit, map, destinations->at( pos ) );
                action->commands.push_back( command );
                actions->push_back( action );
            }
            pos++;
        }
    }
    
    destinations->clear();
    delete destinations;
    
    return actions;
}

std::vector<Point>* GameState::getBestUnitDestination( const Building& headquarter,
                                                       const Building& ownHeadquarter,
                                                       const Unit& unit ) {
    std::vector<Point>* result = new std::vector<Point>;
    result->reserve( TACTIC_POSSIBILITIES );
    
    AreaIterator areaIterator;
    Point unitPosition = unit.getPosition();
    areaIterator.buildArea( unitPosition , unit.getMovement(),
                             MAP_WIDTH, MAP_HEIGHT );
    UnitMovementFilter unitMoveIterator = UnitMovementFilter( areaIterator,
                                                    (Map*)map, unit );
    
    int distanceHQ = unit.getPosition().distance( headquarter.getPosition() );
    int distanceOwnHQ = unit.getPosition().distance( ownHeadquarter.getPosition() );
    int initialDistance = std::min( distanceHQ , distanceOwnHQ );
    int bestDistanceHQ = initialDistance;
    int bestDistanceOwnHQ = initialDistance;
    
    while ( unitMoveIterator.hasNext() ) {
        Point destination = unitMoveIterator.next();
        if( !isInvalidated( destination )  &&
           unit.getPosition().distance( destination ) == unit.getMovement() ) {
            
            int enemyHQDistance = destination.distance(
                                                headquarter.getPosition() );
            int ownHQDistance = destination.distance(
                                                ownHeadquarter.getPosition() );
            
            if( enemyHQDistance < bestDistanceHQ + 2 ) {
                result->push_back( destination );
                bestDistanceHQ = enemyHQDistance;
            }
            
            if( ownHQDistance < bestDistanceOwnHQ + 2 ) {
                result->push_back( destination );
                bestDistanceOwnHQ = ownHQDistance;
            }
        }
    }
    
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
                if( actions.at( i )->size() > sentence.at( i ) ) {
                    Action* action = actions.at( i )->at( sentence.at( i ) );
                    movement->actions.push_back( action );
                }
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
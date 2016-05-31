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

const int GameState::WIN_VALUE;
const int GameState::LOST_VALUE;
const int GameState::NOT_FINISHED;

GameState::GameState( IPlayer* const player, IPlayer* const enemy )
: player( player ), enemy( enemy ) {
    //uglyy
    map = ((Player*) player)->getMap();
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
    bool playerHasCapturedHQ = player->hasCapturedHQ();
    bool enemyHasCapturedHQ = enemy->hasCapturedHQ();
    
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

std::vector<Option*>* GameState::getUnitMoveCommands( Unit* unit ) {
    Point origin = unit->getPosition();
    std::vector<Option*>* moveCommands = new std::vector<Option*>;
    
    std::pair<Point, Point>* boundingArea =
        map->getBoundingArea( origin, unit->getMovement() );
    
    Point start = boundingArea->first;
    Point end = boundingArea->second;
    //iterate over the bounding area
    for ( int i = start.x; i < end.x ; i++ ) {
        for ( int j = start.y; j < end.y; i++ ) {
            Point destination = Point( i, j );
            if( origin.distance( destination ) <= unit->getMovement()
                && map->isValidPosition( destination ) ) {
                MoveCommand* move = new MoveCommand( unit, map, destination );
                moveCommands->push_back( move );
            }
        }
    }
    return moveCommands;
}

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

const int GameState::WIN_VALUE;
const int GameState::LOST_VALUE;
const int GameState::NOT_FINISHED;

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

std::vector<Option*>* GameState::getMovesList( bool maximize ) {
    std::vector<Option*>* moves = new std::vector<Option*>;
    Player* targetPlayer;
    Player* opponent;
    if( maximize ) {
        targetPlayer = (Player*)getPlayer();
        opponent = (Player*)getEnemy();
    } else {
        targetPlayer = (Player*)getEnemy();
        opponent = (Player*)getPlayer();
    }
    for ( Unit* unit : targetPlayer->getAliveUnits() ) {
        std::vector<Option*>* moveOptions = getUnitMoveCommands( unit );
        std::vector<Option*>* attackOptions = getUnitAttackCommands( unit,
                                                        opponent->getAliveUnits() );
        std::vector<Option*>* captureOptions = getUnitCaptureCommands( unit,
                                    targetPlayer , ((Map*)map)->getBuildings() );
        
        moves->insert( moves->end() , moveOptions->begin(), moveOptions->end() );
        moves->insert( moves->end() , attackOptions->begin(), attackOptions->end() );
        moves->insert( moves->end() , captureOptions->begin(), captureOptions->end() );
    }
    
    return moves;
}

std::vector<Option*>* GameState::getUnitMoveCommands( Unit* unit ) {
    Point origin = unit->getPosition();
    if( map->isOnBounds( origin ) ) {
        std::vector<Option*>* moveCommands = new std::vector<Option*>;
        
        std::pair<Point, Point>* boundingArea =
        map->getBoundingArea( origin, unit->getMovement() );
        
        Point start = boundingArea->first;
        Point end = boundingArea->second;
        //iterate over the bounding area
        for ( int i = start.x; i < end.x ; i++ ) {
            for ( int j = start.y; j < end.y; j++ ) {
                Point destination = Point( i, j );
                int range = unit->getMovement();
                if( map->isValidPosition( destination )
                    && unit->onRange( destination, range ) ) {
                    MoveCommand* move = new MoveCommand( unit, (Map*)map,
                                                        destination );
                    moveCommands->push_back( move );
                }
            }
        }
        return moveCommands;
    } else {
        throw InvalidPositionException( origin.x, origin.y,
                                        MAP_WIDTH, MAP_HEIGHT );
    }
}

std::vector<Option*>* GameState::getUnitAttackCommands(
                                Unit *unit, std::vector<Unit*> targets ) {
    Point origin = unit->getPosition();
    if( map->isOnBounds( origin ) ) {
        std::vector<Option*>* attackCommands = new std::vector<Option*>;
        //not sure about this, am i getting a copy of the content
        //referenced by the pointer?
        std::vector<Unit*> targetsOnRange = *getTargetsOnRange( unit, targets );
        
        for ( Unit* targetOnRange : targetsOnRange ) {
            std::pair<Point,Point>* boundingArea =
            map->getBoundingArea( targetOnRange->getPosition(),
                                  unit->getAttackRange() );
            Point start = boundingArea->first;
            Point end = boundingArea->second;
            //iterate over the bounding area
            for ( int i = start.x; i < end.x ; i++ ) {
                for ( int j = start.y; j < end.y; j++ ) {
                    Point destination = Point( i, j );
                    int range = unit->getMovement();
                    if( map->isValidPosition( destination )
                        && unit->onRange( destination, range ) ) {
        
                        MoveCommand* move = new MoveCommand( unit, (Map*)map,
                                                            destination );
                        attackCommands->push_back( move );
                        AttackCommand* attack = new AttackCommand( unit,
                                                                  targetOnRange,
                                                                  (Map*)map );
                        attackCommands->push_back( attack );
                    }
                }
            }

        }
        
        return attackCommands;
    } else {
        throw InvalidPositionException( origin.x, origin.y,
                                       MAP_WIDTH, MAP_HEIGHT );
    }
}

std::vector<Option*>* GameState::getUnitCaptureCommands( Unit* unit, Player* player,
                                             std::vector<Building*> targets  ) {
    Point origin = unit->getPosition();
    if( map->isOnBounds( origin ) ) {
        std::vector<Option*>* captureCommands = new std::vector<Option*>;
        
        std::vector<Building*> buildingsOnRange = *getBuildingsOnRange( unit,
                                                                       targets );
        for ( Building* building : buildingsOnRange ) {
            if( building->getOwnerID() != player->getId() ) {
                MoveCommand* moveCommand = new MoveCommand( unit, (Map*)map,
                                                           building->getPosition() );
                CaptureCommand* captureCommand = new CaptureCommand( player, unit,
                                                                     building );
                captureCommands->push_back( moveCommand );
                captureCommands->push_back( captureCommand );
            }
        }
        
        return captureCommands;
    } else {
        throw InvalidPositionException( origin.x, origin.y,
                                       MAP_WIDTH, MAP_HEIGHT );
    }

}

std::vector<Unit*>* GameState::getTargetsOnRange( Unit* unit,
                                                  const std::vector<Unit *> targets) {
    std::vector<Unit*>* targetsOnRange = new std::vector<Unit*>;
    for ( Unit* target : targets ) {
        int range = unit->getMovement() + unit->getAttackRange();
        if( unit->onRange( target->getPosition(), range ) ) {
            targetsOnRange->push_back( target );
        }
    }
    return targetsOnRange;
}

std::vector<Building*>* GameState::getBuildingsOnRange( Unit* unit,
                                                 std::vector<Building *> targets ) {
    std::vector<Building*>* buildingsOnRange = new std::vector<Building*>;
    for ( Building* target : targets ) {
        int range = unit->getMovement();
        if( unit->onRange( target->getPosition(), range ) ) {
            buildingsOnRange->push_back( target );
        }
    }
    return buildingsOnRange;
}

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

std::vector<Option*>* GameState::getMovesList( Player* player,
                                               Player* opponent ) {
    std::vector<Option*>* moves = new std::vector<Option*>;
    Map* map = (Map*)this->map;
    for ( Unit* unit : player->getAliveUnits() ) {
        std::vector<Action*>* moveActions = unit->getMoveActions( map );
        std::vector<Action*>* attackActions = unit->getAttackActions( map,
                                                opponent->getAliveUnits() );
        std::vector<Action*>* captureActions = unit->getCaptureActions( map,
                                    player, map->getBuildings() );
    }
    
    return moves;
}
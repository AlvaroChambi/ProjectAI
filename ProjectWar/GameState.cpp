//
//  GameState.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 30/5/16.
//  Copyright © 2016 Alvaro Chambi Campos. All rights reserved.
//

#include "GameState.h"
#include "GameException.h"

const int GameState::WIN_VALUE;
const int GameState::LOST_VALUE;
const int GameState::DRAW_VALUE;
const int GameState::NOT_FINISHED;

GameState::GameState( IPlayer* const player, IPlayer* const enemy )
: player( player ), enemy( enemy ) {
    
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
    
    if ( player->hasCapturedHQ() && enemy->hasCapturedHQ() ) {
        throw IllegalStateException( "both captured at the same time" );
    } else if ( !player->hasUnitAlive() && !enemy->hasUnitAlive() ) {
        throw IllegalStateException( "HQ captured without units" );
    } else {
        if( !player->hasUnitAlive() || enemy->hasCapturedHQ() ) {
            return gameScore = GameState::LOST_VALUE;
        }else if( !enemy->hasUnitAlive() || player->hasCapturedHQ() ) {
            return gameScore = GameState::WIN_VALUE;
        }
    }
    
    return gameScore;
}
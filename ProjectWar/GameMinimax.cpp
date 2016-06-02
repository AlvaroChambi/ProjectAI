//
//  GameMinimax.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 30/5/16.
//  Copyright © 2016 Alvaro Chambi Campos. All rights reserved.
//

#include "GameMinimax.h"
#include "GameException.h"

GameMinimax::GameMinimax( GameState* gameState )
: gameState( gameState ) {

}

GameMinimax::~GameMinimax() {

}

int GameMinimax::getGameOverScore() {
    return gameState->getGameOverScore();
}

int GameMinimax::getStaticEvaluation() {
    return 0;
}

//TODO: Implement getMaxMovesList and getMinMovesList in the minimax
std::vector<Option*>& GameMinimax::getMovesList( const bool maximize ) {
    if ( maximize ) {
        return *gameState->getMovesList( (Player*)gameState->getPlayer(),
                                         (Player*)gameState->getEnemy() );
    } else {
        return *gameState->getMovesList( (Player*)gameState->getEnemy(),
                                        (Player*)gameState->getPlayer() );
    }
}

void GameMinimax::processMove( Option *move ) {

}

void GameMinimax::unprocessMove( Option *move ) {

}

int GameMinimax::minimaxMin( const int bestSoFar, const int score ) {
    return 0;
}

int GameMinimax::minimaxMax( const int bestSoFar, const int score,
                            Option *move, Option **bestMove ) {
    return 0;
}
//
//  GameMinimax.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 30/5/16.
//  Copyright © 2016 Alvaro Chambi Campos. All rights reserved.
//

#include "GameMinimax.h"
#include "GameException.h"

static const int INFINITE = std::numeric_limits<int>::max();
GameMinimax::GameMinimax( MapContext* mapContext )
: mapContext( mapContext ) {
    gameState = new GameState( (IPlayer*)&mapContext->getPlayer(),
                               (IPlayer*)&mapContext->getOpponent(),
                               mapContext );
    heuristicFunction = new HeuristicFunction(
                                *(Player*)gameState->getPlayer(),
                                *(Player*)gameState->getEnemy() );
}

GameMinimax::~GameMinimax() {

}

int GameMinimax::getGameOverScore() {
    return gameState->getGameOverScore();
}

int GameMinimax::getStaticEvaluation() {
    return heuristicFunction->getStaticEvaluation();
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
    move->execute();
}

void GameMinimax::unprocessMove( Option *move ) {
    move->cancel();
}

int GameMinimax::minimaxMin( const int bestSoFar, const int score ) {
    int result = bestSoFar;
    if (score < bestSoFar || bestSoFar == INFINITE) {
        result = score;
    }
    
    return result;
}

int GameMinimax::minimaxMax( const int bestSoFar, const int score,
                            Option *move, Option **bestMove, bool topBranch ) {
    int result = bestSoFar;
    
    if ( score > bestSoFar || bestSoFar == INFINITE ) {
        result = score;
        //TODO: Move best move update to another method in Minimax
        if( topBranch ) {
            *bestMove = move;
        }
    }
    
    return result;
}
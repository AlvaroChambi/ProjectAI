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
GameMinimax::GameMinimax( MapContext& mapContext,
                          const ActionsProvider& actionsProvider )
: mapContext( mapContext ), actionsProvider( actionsProvider ) {
    heuristicFunction = new HeuristicFunction( );
}

GameMinimax::~GameMinimax() {

}

int GameMinimax::getGameOverScore() {
    return heuristicFunction->getGameOverScore( mapContext.getPlayer(),
                                                mapContext.getOpponent() );
}

int GameMinimax::getStaticEvaluation() {
    return heuristicFunction->getStaticEvaluation( mapContext.getPlayer(),
                                                   mapContext.getOpponent() );
}

MovementsList& GameMinimax::getMovesList( const bool maximize ) {
    int numActions = 4;
    if ( maximize ) {
        return actionsProvider.generateMovements( mapContext.getPlayer().getId(),
                                                  numActions );
    } else {
        return actionsProvider.generateMovements( mapContext.getOpponent().getId(),
                                                  numActions );
    }
}

void GameMinimax::processMove( Option *move ) {
    move->execute( mapContext );
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
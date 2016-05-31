//
//  TacticMinimax.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 25/4/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#include "TacticMinimax.h"
#include <string>
#include <vector>

TacticMinimax::TacticMinimax( GameState* game )
: tacticBuilder( game ), gameState( game ) {
    
}

TacticMinimax::~TacticMinimax() {

}

int TacticMinimax::getGameOverScore() {
    return gameState->getGameOverScore();
}

int TacticMinimax::getStaticEvaluation() {
    //TODO: Will be implemented in a future user story
    return 0;
}

std::vector<Option*>& TacticMinimax::getMovesList( const bool maximize ) {
    std::vector<Option*>* moves = new std::vector<Option*>();
    
    //TODO: Will be implemented in a future user story
    return *moves;
}


void TacticMinimax::processMove( Option *move ) {
    move->execute();
}

void TacticMinimax::unprocessMove( Option *move ) {
    move->cancel();
}

int TacticMinimax::minimaxMax( int bestSoFar, int score,
                               Option *move, Option **bestMove ) {
    int result = bestSoFar;
    
    if (score > bestSoFar || bestSoFar == INFINITE) {
        result = score;
        *bestMove = move;
    }
    
    return result;
}

int TacticMinimax::minimaxMin( int bestSoFar, int score ) {
    
    int result = bestSoFar;
    if (score < bestSoFar || bestSoFar == INFINITE) {
        result = score;
    }
    
    return result;
}
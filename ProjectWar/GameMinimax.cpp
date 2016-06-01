//
//  GameMinimax.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 30/5/16.
//  Copyright © 2016 Alvaro Chambi Campos. All rights reserved.
//

#include "GameMinimax.h"

GameMinimax::GameMinimax( GameState* gameState )
: gameState( gameState ){

}

GameMinimax::~GameMinimax() {

}

int GameMinimax::getGameOverScore() {
    return gameState->getGameOverScore();
}

int GameMinimax::getStaticEvaluation() {
    return 0;
}

std::vector<Option*>& GameMinimax::getMovesList( const bool maximize ) {
    std::vector<Option*> vector;
    return vector;
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
//
//  GameMinimax.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 30/5/16.
//  Copyright © 2016 Alvaro Chambi Campos. All rights reserved.
//

#include "GameMinimax.h"
#include "GameException.h"

GameMinimax::GameMinimax( GameState* gameState ) {

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
    std::vector<Option*>* moves = new std::vector<Option*>;
    
    Player* player;
    if ( maximize ) { //AI
        player = (Player*)gameState->getPlayer();
    } else { //Player
        player = (Player*)gameState->getEnemy();
    }
    
    //for the given player
        // for each available unit generate the set of valid movements
            // unit - getAllAvailable move position ->          start position - end position
            // unit - getAllAvailable enemy units on range ->   unit - target unit - end position
            // unit - getAllAvailable buildings on range ->     unit - target building
    
    for ( Unit* unit : player->getAliveUnits() ) {
        
    }
    
    return *moves;
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
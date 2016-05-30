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

void printGray(std::vector<std::string> arr) {
    for (int i = 0 ; i < arr.size() ; i++ )
        std::cout << arr[i] << std::endl;
    
}

// This function generates all n bit Gray codes and prints the
// generated codes
std::vector<std::string> generateGraySequence(int n) {
    // 'arr' will store all generated codes
    std::vector<std::string> arr;
    // start with one-bit pattern
    arr.push_back("A");
    arr.push_back("C");
    
    // Every iteration of this loop generates 2*i codes from previously
    // generated i codes.
    int i, j;
    for (i = 2; i < (1<<n); i = i<<1)
    {
        // Enter the prviously generated codes again in arr[] in reverse
        // order. Nor arr[] has double number of codes.
        for (j = i-1 ; j >= 0 ; j--)
            arr.push_back(arr[j]);
        
        // append A to the first half
        for (j = 0 ; j < i ; j++)
            arr[j] = "A" + arr[j];
        
        // append C to the second half
        for (j = i ; j < 2*i ; j++)
            arr[j] = "C" + arr[j];
    }
    
    return arr;
}

bool TacticMinimax::isGameOver( ) {
    Player* player = gameState->player;
    Player* enemy = gameState->enemy;
    
    bool result = false;
    if (!player->hasUnitAlive() || enemy->hasCapturedHQ()) {
        result = true;
    }
    if (!enemy->hasUnitAlive() || player->hasCapturedHQ()) {
        result = true;
    }
    
    return result;
}

int TacticMinimax::getGameOverScore() {
    int gameScore = GameState::DRAW_VALUE;
    //WIN = 1, LOSE = -1
    //if hq is captured or all enemys of one side are dead
    Player* player = gameState->player;
    Player* enemy = gameState->enemy;
    
    if (!player->hasUnitAlive() || enemy->hasCapturedHQ()) {
        gameScore = GameState::LOST_VALUE;
    }
    if (!enemy->hasUnitAlive() || player->hasCapturedHQ()) {
        gameScore = GameState::WIN_VALUE;
    }
    
    return gameScore;
}

int TacticMinimax::getStaticEvaluation() {
    Player* player = gameState->player;
    Player* enemy = gameState->enemy;
    Point point;
    int result = GameState::DRAW_VALUE;
    for (Unit* unit : player->getUnitList()) {
        point.x = 2;
        point.y = 2;
        result = result + unit->getHP() * 0.1;
        result = result - unit->getPosition().distance(point);
        
    }
    
    for (Unit* unit : enemy->getUnitList()) {
        point.x = 12;
        point.y = 6;
        result = result - unit->getHP() * 0.1;
        result = result + unit->getPosition().distance(point);
    }
    
    return result;
}

std::vector<Option*>& TacticMinimax::getMovesList( const bool maximize ) {
    Player* player = nullptr;
    Player* enemy = nullptr;
    
    std::vector<Option*>* moves = new std::vector<Option*>();
    
    if ( maximize ) {
        player = gameState->player;
        enemy = gameState->enemy;
    }else{
        player = gameState->enemy;
        enemy = gameState->player;
    }
    //TODO IMPROVE THIS
    std::vector<std::string> tacticMovements =
    generateGraySequence((int)player->getAliveUnits().size());
    int sequenceSize = (int)tacticMovements.size();
    for(int i = 0; i<sequenceSize; i++){
        std::string tacticSequence = tacticMovements.back();
        tacticMovements.pop_back();
        Tactic* movement = tacticBuilder.createTactic(player, enemy, tacticSequence);
        moves->push_back(movement);
    }
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
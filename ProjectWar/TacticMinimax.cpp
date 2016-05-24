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

TacticMinimax::TacticMinimax(GameState& game) : Minimax(game), tacticBuilder(game)
{
    
}

TacticMinimax::~TacticMinimax()
{

}

void printGray(std::vector<std::string> arr){
    for (int i = 0 ; i < arr.size() ; i++ )
        std::cout << arr[i] << std::endl;
    
}

// This function generates all n bit Gray codes and prints the
// generated codes
std::vector<std::string> generateGraySequence(int n)
{
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


void TacticMinimax::getMovesList(int depth, std::list<Option*>& moves)
{
    Player* player = nullptr;
    Player* enemy = nullptr;
    if (depth%2 != 0) {
        //AI turn
        player = game.player;
        enemy = game.enemy;
    }else{
        player = game.enemy;
        enemy = game.player;
    }
    //TODO IMPROVE THIS
    std::vector<std::string> tacticMovements = generateGraySequence((int)player->getUnitList().size());
    int sequenceSize = (int)tacticMovements.size();
    for(int i = 0; i<sequenceSize; i++){
        std::string tacticSequence = tacticMovements.back();
        tacticMovements.pop_back();
        Tactic* movement = tacticBuilder.createTactic(player, enemy, tacticSequence);
        moves.push_back(movement);
    }
}

int TacticMinimax::minOrMax(int bestSofar, int score, int depth)
{
    int result = bestSofar;
    
    if (depth%2 == 0) {
        //min
        std::cout << "MIN \n";
        if (score < bestSofar || bestSofar == Minimax::INFINITE) {
            result = score;
        }
    }else{
        //max
        std::cout << "MAX \n";
        if (score > bestSofar || bestSofar == Minimax::INFINITE) {
            result = score;
        }
    }
    std::cout << " bestSoFar: " + std::to_string(bestSofar)+
    " Score: " + std::to_string(score) + "\n";

    return result;
}

Minimax* TacticMinimax::makeMinimax()
{
    return new TacticMinimax(game);
}

int TacticMinimax::getGameOverScore()
{
    int gameScore = GameState::DRAW_VALUE;
    //WIN = 1, LOSE = -1
    //if hq is captured or all enemys of one side are dead
    Player* player = game.player;
    Player* enemy = game.enemy;
    
    if (!player->hasUnitAlive() || enemy->hasCapturedHQ()) {
        gameScore = GameState::LOST_VALUE;
    }
    if (!enemy->hasUnitAlive() || player->hasCapturedHQ()) {
        gameScore = GameState::WIN_VALUE;
    }
    
    return gameScore;
}

int TacticMinimax::getWorstScore()
{
    return Minimax::INFINITE;
}

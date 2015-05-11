//
//  TacticMinimax.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 25/4/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#include "TacticMinimax.h"

TacticMinimax::TacticMinimax(GameState& game) : Minimax(game), tacticBuilder(game)
{

}

TacticMinimax::~TacticMinimax()
{

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
    std::cout << "Attack tactic movements: \n";
    Tactic* attackTactic = tacticBuilder.createTactic(ATTACK_TACTIC, player, enemy);
    std::cout << "Capture tactic movements: \n";
    Tactic* captureTactic = tacticBuilder.createTactic(CAPTURE_TACTIC, player, enemy);
    
    moves.push_back(attackTactic);
    moves.push_back(captureTactic);
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

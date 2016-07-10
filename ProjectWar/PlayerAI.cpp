//
//  PlayerAI.cpp
//  ProjectWar
//
//  Created by Pablo Luis Gutierrez on 09/04/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#include "PlayerAI.h"
#include "Map.h"
#include "MinimaxAlgorithm.hpp"
#include "DotPath.h"
#include "GameMinimax.h"
#include <stdio.h>
#include <chrono>

PlayerAI::PlayerAI() : Player() {
    setType(AI_PLAYER);
}

PlayerAI::PlayerAI( int id )
:  Player(id) {
    setType(AI_PLAYER);
}

PlayerAI::~PlayerAI() {

}

void PlayerAI::play( MapContext* mapContext ) {
    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
    std::cout << "Minimax on progress..." << std::endl;
    executeMinimax( mapContext );
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "Minimax took "
    << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
    << "ms.\n";
}



void PlayerAI::executeMinimax( MapContext* mapContext ) {
    MinimaxAlgorithm* algorithm =
        new MinimaxAlgorithm( new GameMinimax( mapContext ) );
    algorithm->minimax( 4 );
    Movement* movement = (Movement*)algorithm->getBestMove();
    if( movement != nullptr ) {
        movement->execute();
    }
}
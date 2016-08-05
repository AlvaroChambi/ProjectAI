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
#include "ActionsProvider.h"

#include <stdio.h>
#include <chrono>

#include "DotPath.h"

PlayerAI::PlayerAI() : Player() {
    setType(AI_PLAYER);
}

PlayerAI::PlayerAI( int id )
:  Player(id) {
    setType(AI_PLAYER);
}

PlayerAI::~PlayerAI() {

}

Movement* PlayerAI::play( MapContext* mapContext ) {
    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
    std::cout << "Minimax on progress..." << std::endl;
    Movement* result = executeMinimax( mapContext );
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "Minimax took "
    << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
    << "ms.\n";
    return result;
}



Movement* PlayerAI::executeMinimax( MapContext* mapContext ) {
    GameMinimax* gameMinimax = new GameMinimax( *mapContext ,
                                                ActionsProvider( *mapContext ) );
    MinimaxAlgorithm* algorithm =
        new MinimaxAlgorithm( gameMinimax );
    DotBuilder logger;
    algorithm->setDebugLogger( &logger );
    algorithm->minimax( 4 );
    std::cout << "nodes evaluated:  " << logger.getIndex() << std::endl;
    Movement* movement = (Movement*)algorithm->getBestMove();
    return movement;
}
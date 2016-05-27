//
//  MinimaxAlgorithm.hpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 26/5/16.
//  Copyright © 2016 Alvaro Chambi Campos. All rights reserved.
//

#ifndef MinimaxAlgorithm_hpp
#define MinimaxAlgorithm_hpp

#include "Minimax.h"
#include "GameState.h"
#include "GraphLogger.h"

class MinimaxAlgorithm {
    
public:
    static const int INFINITE = std::numeric_limits<int>::max();
    MinimaxAlgorithm( Minimax* minimax );
    MinimaxAlgorithm( Minimax* minimax, GraphLogger* graphLogger );
    ~MinimaxAlgorithm();
    
    void minimax( int ply );
    int minimax( int ply, int alpha, int beta, bool maximize );
    
    Option* getBestMove();
    
private:
    GraphLogger* graphLogger;
    Minimax* miniMax;
    Option* bestMove;
};

#endif /* MinimaxAlgorithm_hpp */

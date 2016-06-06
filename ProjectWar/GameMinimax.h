//
//  GameMinimax.h
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 30/5/16.
//  Copyright © 2016 Alvaro Chambi Campos. All rights reserved.
//

#ifndef GameMinimax_h
#define GameMinimax_h

#include "Minimax.h"
#include "GameState.h"
#include "HeuristicFunction.h"

class GameMinimax : public Minimax {
public:
    GameMinimax( GameState* gameState );
    ~GameMinimax();
    
    int getGameOverScore();
    int getStaticEvaluation();
    std::vector<Option*>& getMovesList( const bool maximize );
    void processMove(Option* move);
    void unprocessMove(Option* move);
    int minimaxMin( const int bestSoFar, const int score );
    int minimaxMax( const int bestSoFar, const int score,
                          Option* move, Option** bestMove );
    
private:
    GameState* gameState;
    HeuristicFunction* heuristicFunction;
};

#endif /* GameMinimax_h */

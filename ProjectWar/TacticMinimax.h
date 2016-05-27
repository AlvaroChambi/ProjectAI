//
//  TacticMinimax.h
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 25/4/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#ifndef __ProjectWar__TacticMinimax__
#define __ProjectWar__TacticMinimax__

#include <stdio.h>
#include "Minimax.h"
#include "TacticBuilder.h"

class TacticMinimax : public Minimax {
public:
    static const int INFINITE = std::numeric_limits<int>::max();
    TacticMinimax( GameState* gameState );
    ~TacticMinimax();
    
    bool isGameOver();
    
    int getGameOverScore();
    int getStaticEvaluation();
    
    std::vector<Option*>& getMovesList( const bool maximize );
    
    void processMove( Option* move );
    void unprocessMove( Option* move );
    
    int minimaxMin( const int bestSoFar, const int score );
    int minimaxMax( const int bestSoFar, const int score,
                    Option* move, Option** bestMove );
    
private:
    TacticBuilder tacticBuilder;
    GameState* gameState;
    std::vector<Option*> moves;
};

#endif /* defined(__ProjectWar__TacticMinimax__) */

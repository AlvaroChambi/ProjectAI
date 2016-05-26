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

class TacticMinimax : public Minimax
{
public:
    TacticMinimax(GameState& gameState);
    virtual ~TacticMinimax();
    int minOrMax( int bestSoFar,
                  int score, int depth,
                  Option* move ,Option** bestMove );
    
    int minimaxMax( int bestSoFar, int score,
                   Option* move ,Option** bestMove );
    int minimaxMin( int bestSoFar, int score );
    
    Minimax* makeMinimax();
    int getGameOverScore();
    int getWorstScore();
    void getMovesList( const bool maximize ,std::list<Option*>& moves );
private:
    TacticBuilder tacticBuilder;
};

#endif /* defined(__ProjectWar__TacticMinimax__) */

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
    int minOrMax( int bestSoFar, int score, int depth );
    Minimax* makeMinimax();
    int getGameOverScore();
    int getWorstScore();
    void getMovesList(int depth, List<Option*>& moves);
private:
    TacticBuilder tacticBuilder;
};

#endif /* defined(__ProjectWar__TacticMinimax__) */

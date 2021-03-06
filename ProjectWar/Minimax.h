#ifndef Minimax_h
#define Minimax_h

#include "Option.h"
#include <vector>
#include "MovementsList.h"

class Minimax {
public:
    virtual int getGameOverScore() = 0;
    virtual int getStaticEvaluation() = 0;
    virtual MovementsList& getMovesList( const bool maximize ) = 0;
    virtual void processMove(Option* move) = 0;
    virtual void unprocessMove(Option* move) = 0;
    virtual int minimaxMin( const int bestSoFar, const int score ) = 0;
    virtual int minimaxMax( const int bestSoFar, const int score,
                            Option* move, Option** bestMove, bool topBranch ) = 0;
};

#endif /* GameMinimax_h */

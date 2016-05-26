#ifndef GameMinimax_h
#define GameMinimax_h

#include "Option.h"
#include <vector>

class Minimax {
public:
    virtual bool isGameOver() = 0;
    virtual int getGameOverScore() = 0;
    virtual int getStaticEvaluation() = 0;
    virtual std::vector<Option*>& getMovesList( const bool maximize ) = 0;
    virtual void processMove(Option* move) = 0;
    virtual void unprocessMove(Option* move) = 0;
    virtual int minimaxMin( const int bestSoFar, const int score ) = 0;
    virtual int minimaxMax( const int bestSoFar, const int score,
                            Option* move, Option** bestMove ) = 0;
};

#endif /* GameMinimax_h */

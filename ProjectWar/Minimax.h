//
//  Minimax.h
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 25/4/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#ifndef ProjectWar_Minimax_h
#define ProjectWar_Minimax_h

#include "GameState.h"
#include "Option.h"
#include <limits>
#include <list>

#include <chrono>
#include <thread>
class Minimax
{
public:
    static const int INFINITE = std::numeric_limits<int>::max();
    
    Minimax( GameState& game ) : game(game)
    {}
    virtual ~Minimax() {}
    
    int minimax( int depthSearch ) {
        int alpha = -INFINITE;
        int beta = INFINITE;
        bool maximize = true;
        return minimax( depthSearch, alpha, beta, maximize );
    }
    
    int minimax ( int depthSearch, int alpha, int beta, bool maximize ) {
        if (game.isGameOver()) {
            // can mock this
            return getGameOverScore();
        }
        
        if(depthSearch == 0) {
            //can mock this
            return game.getStaticEvaluation();
        }
        
        Minimax* child = makeMinimax();
        int bestSoFar;
        
        // can mock this
        std::list<Option*> moves;
        getMovesList( maximize, moves );
        //
        bestSoFar = INFINITE;
        for (Option* option : moves) {
            // can mock this
            game.processMove(option);
            //
            int score = child->minimax( depthSearch -1,
                                       alpha, beta, !maximize );
            
            if( maximize ) {
                // can mock this
                bestSoFar = minimaxMax( bestSoFar, score, option ,&bestMove );
                //

                alpha = std::max(alpha, bestSoFar);
            } else {
                bestSoFar = minimaxMin( bestSoFar, score );
                
                beta = std::min(beta, bestSoFar);
            }
            
            // can mock this
            game.unprocessMove(option);
            //
            
            if ( beta <= alpha ) {
                return bestSoFar;
            }
        }
        return bestSoFar;
    }
    Option* getMove()
    {
        return bestMove;
    }
protected:
    virtual int minOrMax( int bestSoFar, int score, int depth,
                          Option* move ,Option** bestMove) = 0;
    
    virtual int minimaxMin( int bestSoFar, int score ) = 0;
    virtual int minimaxMax( int bestSoFar, int score,
                            Option* move, Option** bestMove ) = 0;
    
    virtual Minimax* makeMinimax() = 0;
    virtual int getGameOverScore() = 0;
    virtual int getWorstScore() = 0;
    virtual void getMovesList( const bool maximize, std::list<Option*>&) = 0;
    GameState& game;
    
private:
    Option* bestMove;
};

#endif

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
    static const int INFINITE = -std::numeric_limits<int>::max();
    
    Minimax( GameState& game ) : game(game)
    {}
    virtual ~Minimax() {}
    
    int minimax( int depthSearch )
    {
        int depth = 1;
        return minimax(depthSearch, depth);
    }
    
    int minimax(int depthSearch, int depth){
        
        if (game.isGameOver()) {
            return getGameOverScore();
        }
        
        if(depthSearch == 0){
            //static evaluation
            return game.getStaticEvaluation();
        }
        Minimax* child = makeMinimax();
        int bestSoFar = getWorstScore();
        std::list<Option*> moves;
        getMovesList(depth, moves); //Tactic list for the given player
        for (Option* option : moves) {
            move = option;
            game.processMove(move);
            //std::this_thread::sleep_for(std::chrono::milliseconds(250));
            int score = child->minimax( depthSearch -1, depth +1 );
            
            std::cout << "//////////////NODE (on back)///////////////////\n";
            std::cout << "score: " + std::to_string(score) + "\n";
            std::cout << "depth: " + std::to_string(depth) + "\n";
            std::cout << "depthSearch: " + std::to_string(depthSearch) + "\n";
            std::cout << "minOrMax: ";
            
            bestSoFar = minOrMax(bestSoFar, score, depth);
            
            std::cout << "NodeValue: " + std::to_string(bestSoFar) + "\n";
            game.unprocessMove(move);
        }
        return bestSoFar;
    }
    
    Option* getMove()
    {
        return move;
    }
protected:
    virtual int minOrMax( int bestSoFar, int score, int depth) = 0;
    virtual Minimax* makeMinimax() = 0;
    virtual int getGameOverScore() = 0;
    virtual int getWorstScore() = 0;
    virtual void getMovesList(int depth, std::list<Option*>&) = 0;
    GameState& game;
    
private:
    Option* move;
};

#endif

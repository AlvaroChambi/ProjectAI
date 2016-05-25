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
    static const int MINUSINFINITE = std::numeric_limits<int>::min();
    
    Minimax( GameState& game ) : game(game)
    {}
    virtual ~Minimax() {}
    
    int minimax( int depthSearch )
    {
        int depth = 1;
        int alpha = -INFINITE;
        int beta = INFINITE;
        //return minimax(depthSearch, depth);
        return minimax(depthSearch, depth, alpha, beta);
    }
    
    int max(int n, int m){
        int result;
        if(n>m){
            result = n;
        }
        else{
            result = m;
        }
        return result;
    }
    
    int min (int n, int m){
        int result;
        if(n<m){
            result = n;
        }
        else{
            result = m;
        }
        return result;
    }
    
    int minimax (int depthSearch, int depth, int alpha, int beta){
        if (game.isGameOver()) {
            return getGameOverScore();
        }
        
        if(depthSearch == 0){
            //static evaluation
            return game.getStaticEvaluation();
        }
        
        Minimax* child = makeMinimax();
        int bestSoFar;
        if (depth%2 != 0){
            //Maximizing
            bestSoFar= -INFINITE;
            std::list<Option*> moves;
            getMovesList(depth, moves); //Tactic list for the given player
            for (Option* option : moves) {
                game.processMove(option);
                int score = child->minimax(depthSearch -1, depth +1, alpha, beta );
                bestSoFar = minOrMax(bestSoFar, score, depth, option ,&bestMove);
                std::cout << "//////////////NODE (on back)///////////////////\n";
                std::cout << "score: " + std::to_string(score) + "\n";
                game.unprocessMove(option);
                alpha = max(alpha, bestSoFar);

                if (beta <= alpha){
                    return bestSoFar;
                }
            }
        }
        else {
            std::list<Option*> moves;
            getMovesList(depth, moves); //Tactic list for the given player
            bestSoFar = INFINITE;
            for (Option* option : moves) {
                game.processMove(option);
                int score = child->minimax(depthSearch -1, depth +1, alpha, beta );
                bestSoFar = minOrMax(bestSoFar, score, depth, option ,&bestMove);
                
                std::cout << "//////////////NODE (on back)///////////////////\n";
                std::cout << "score: " + std::to_string(score) + "\n";
                
                game.unprocessMove(option);
                beta = min(beta, bestSoFar);
                
                if (beta <= alpha)
                    return bestSoFar;
                
            }
        }return bestSoFar;
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
            game.processMove(option);
            //std::this_thread::sleep_for(std::chrono::milliseconds(250));
            int score = child->minimax( depthSearch -1, depth +1 );
            
            std::cout << "//////////////NODE (on back)///////////////////\n";
            std::cout << "score: " + std::to_string(score) + "\n";
            std::cout << "depth: " + std::to_string(depth) + "\n";
            std::cout << "depthSearch: " + std::to_string(depthSearch) + "\n";
            std::cout << "minOrMax: ";
            
            bestSoFar = minOrMax(bestSoFar, score, depth, option ,&bestMove);
            
            std::cout << "NodeValue: " + std::to_string(bestSoFar) + "\n";
            game.unprocessMove(option);
        }
        return bestSoFar;
    }
    
    Option* getMove()
    {
        return bestMove;
    }
protected:
    virtual int minOrMax( int bestSoFar, int score, int depth, Option* move ,Option** bestMove) = 0;
    virtual Minimax* makeMinimax() = 0;
    virtual int getGameOverScore() = 0;
    virtual int getWorstScore() = 0;
    virtual void getMovesList(int depth, std::list<Option*>&) = 0;
    GameState& game;
    
private:
    Option* bestMove;
};

#endif

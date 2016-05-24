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
        
        int bestChildrenScore= 0;
        Option* bestChildrenMove = nullptr;
        
        
        if (game.isGameOver()) {
            return getGameOverScore();
        }
        
        if(depthSearch == 0){
            //static evaluation
            return game.getStaticEvaluation();
        }
        Minimax* child = makeMinimax();
        //int bestSoFar = getWorstScore();
        
        std::list<Option*> moves;
        getMovesList(depth, moves); //Tactic list for the given player
        for (Option* option : moves) {
            int childScore;
            bool first = true;
            Option* bestMovement;
            bestMovement = option;
            game.processMove(bestMovement);
            //std::this_thread::sleep_for(std::chrono::milliseconds(350));
            //int score = child->minimax( depthSearch -1, depth +1 );
            childScore = child->minimax( depthSearch -1, depth +1 );

            std::cout << "//////////////NODE (on back)///////////////////\n";
            std::cout << "score: " + std::to_string(childScore) + "\n";
            std::cout << "depth: " + std::to_string(depth) + "\n";
            std::cout << "depthSearch: " + std::to_string(depthSearch) + "\n";
            std::cout << "minOrMax: ";
            
            //childScore = minOrMax(bestSoFar, score, depth);
            
            // First child
            
            if (bestChildrenMove==nullptr) {
             
             bestChildrenScore = childScore;
                bestChildrenMove = bestMovement;
                first = false;
              
             
            }
             
            else {
                // We maximize
                if (depth%2 !=0) {
                    if (childScore > bestChildrenScore) {
                        bestChildrenScore = childScore;
                        bestChildrenMove = bestMovement;
                        first = false;
                    }
                }
                
                // We minimize
                else {
                    if (childScore < bestChildrenScore) {
                        bestChildrenScore = childScore;
                        bestChildrenMove = bestMovement;
                        first = false;
                    }
                    
                }
            }
            
            
            std::cout << "NodeValue: " + std::to_string(bestChildrenScore) + "\n";
            game.unprocessMove(bestMovement);
        }
        if (move != nullptr) {
            move = bestChildrenMove;
        }
        
        return bestChildrenScore;
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

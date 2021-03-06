
#include "MinimaxAlgorithm.hpp"
#include <stdio.h>
#include <algorithm>
#include "MovementsList.h"

MinimaxAlgorithm::MinimaxAlgorithm( Minimax* minimax )
: miniMax( minimax ), bestMove( nullptr ), graphLogger( nullptr ) {

}

MinimaxAlgorithm::~MinimaxAlgorithm() {

}

void MinimaxAlgorithm::minimax( int ply ) {
    int alpha = -INFINITE;
    int beta = INFINITE;
    bool maximize = true;
    maxPly = ply;
    minimax( ply, alpha, beta, maximize );
}

int MinimaxAlgorithm::minimax( int ply, int alpha,
                               int beta, bool maximize ) {
    
    int gameOverScore = miniMax->getGameOverScore();
    if ( gameOverScore != GameState::NOT_FINISHED ) {
        if( graphLogger != nullptr ) {
            graphLogger->addToPath( graphLogger->getIndex() );
            graphLogger->nextPath();
        }
        return gameOverScore;
    }
    
    if( ply <= 0 ) {
        if( graphLogger != nullptr ) {
            graphLogger->addToPath( graphLogger->getIndex() );
            graphLogger->nextPath();
        }
        return miniMax->getStaticEvaluation();
    }
    
    //TODO: options memory cleanup
    MovementsList& movesList = miniMax->getMovesList( maximize );
    //std::cout << "Reserved: " << movesList.getMovementsVector().size() << std::endl;
    std::vector<Option*> moves = movesList.getMovementsVector();
    
    int bestSoFar = INFINITE;
    
    std::string actualNode = "";
    if( graphLogger != nullptr ){
        actualNode = graphLogger->getIndex();
        graphLogger->addToPath( actualNode );
    }

    for ( Option* option : moves ) {
        miniMax->processMove(option);
        int score = minimax( ply-1, alpha, beta, !maximize );
        miniMax->unprocessMove(option);
        bool topBranch = ply == maxPly;
        if( maximize ) {
            bestSoFar = miniMax->minimaxMax( bestSoFar, score,
                                             option ,&bestMove, topBranch );
            alpha = std::max(alpha, bestSoFar);
        } else {
            bestSoFar = miniMax->minimaxMin( bestSoFar, score );
            
            beta = std::min(beta, bestSoFar);
        }
        
        if ( beta <= alpha ) {
            if( graphLogger != nullptr ) {
                graphLogger->nextPath();
            }
            delete &movesList;
            return bestSoFar;
        } else {
            if( graphLogger != nullptr ) {
                graphLogger->addToPath( actualNode );
            }
        }
    }
    
    delete &movesList;
    return bestSoFar;
}

void MinimaxAlgorithm::setDebugLogger( GraphLogger *graphLogger ) {
    this->graphLogger = graphLogger;
}

std::string MinimaxAlgorithm::getGraphLog() {
    if ( graphLogger != nullptr ) {
        return graphLogger->getLog();
    }
    return "";
}

Option* MinimaxAlgorithm::getBestMove() {
    return bestMove;
}
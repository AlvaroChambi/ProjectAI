
#include "MinimaxAlgorithm.hpp"

MinimaxAlgorithm::MinimaxAlgorithm( Minimax* minimax )
: miniMax( minimax ), bestMove( nullptr ) {

}

MinimaxAlgorithm::~MinimaxAlgorithm() {

}

void MinimaxAlgorithm::minimax( int ply ) {
    int alpha = -INFINITE;
    int beta = INFINITE;
    bool maximize = true;
    minimax( ply, alpha, beta, maximize );
}

int MinimaxAlgorithm::minimax( int ply, int alpha,
                               int beta, bool maximize ) {
    
    if ( miniMax->isGameOver() ) {
        return miniMax->getGameOverScore();
    }
    
    if( ply <= 0 ) {
        return miniMax->getStaticEvaluation();
    }
    
    //TODO: options memory cleanup
    std::vector<Option*>& moves = miniMax->getMovesList( maximize );
    int bestSoFar = INFINITE;
    
    for (Option* option : moves) {
        miniMax->processMove(option);
        int score = minimax( ply-1, alpha, beta, !maximize );
        
        if( maximize ) {
            bestSoFar = miniMax->minimaxMax( bestSoFar, score,
                                             option ,&bestMove );
            alpha = std::max(alpha, bestSoFar);
        } else {
            bestSoFar = miniMax->minimaxMin( bestSoFar, score );
            
            beta = std::min(beta, bestSoFar);
        }
        
        miniMax->unprocessMove(option);
        
        if ( beta <= alpha ) {
            return bestSoFar;
        }
    }
    return bestSoFar;
}

Option* MinimaxAlgorithm::getBestMove() {
    return bestMove;
}
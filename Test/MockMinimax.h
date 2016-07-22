

#ifndef MockMinimax_h
#define MockMinimax_h

#include "gmock/gmock.h"
#include "Minimax.h"

class MockMinimax : public  Minimax {
public:
    MOCK_METHOD0( getGameOverScore, int( ) );
    MOCK_METHOD0( getStaticEvaluation, int() );
    MOCK_METHOD1( getMovesList, std::vector<Option*>( const bool maximize ) );
    MOCK_METHOD1( processMove, void( Option* option ) );
    MOCK_METHOD1( unprocessMove, void( Option* option ) );
    
    MOCK_METHOD2( minimaxMin, int( int bestSoFar, int score ) ) ;
    MOCK_METHOD5( minimaxMax, int( int bestSoFar, int score,
                                   Option* move, Option** bestMove, bool topBranch ) );
};
#endif /* MockMinimax_h */

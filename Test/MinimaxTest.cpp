#include <iostream>
#include "MinimaxAlgorithm.hpp"
#include "MockMinimax.h"
#include "MockOption.h"
#include "MockGraphLogger.h"
#include "gtest/gtest.h"
#include "MovementsList.h"

using ::testing::Return;
class MinimaxTest : public ::testing::Test {
public:
    const int INFINITE = std::numeric_limits<int>::max();
    MinimaxTest() {
        
    }
    
    virtual void SetUp() {
        minimax = new MinimaxAlgorithm( &mockMinimax );
        mockMoves = new MovementsList();
    }
    
    virtual void TearDown() {

    }
    std::vector<Option*> moves;
    MovementsList* mockMoves;
    MinimaxAlgorithm* minimax;
    MockMinimax mockMinimax;
    MockGraphLogger mockGraphLogger;
};

TEST_F( MinimaxTest, MinimaxReachGameOverTest ) {
    EXPECT_CALL( mockMinimax , getGameOverScore() )
    .WillOnce( Return( 10 ) );
    
    ASSERT_EQ( 10, minimax->minimax( 10, 0, 0, true ) );
}

TEST_F( MinimaxTest, MinimaxReachPlyLimitTest ) {
    EXPECT_CALL( mockMinimax , getStaticEvaluation() )
    .WillOnce( Return( 10 ) );
    
    int ply = 0;
    
    ASSERT_EQ( 10, minimax->minimax( ply, 0, 0, true ) );
}

TEST_F( MinimaxTest, MinimaxMaximizeEmptyMoves ) {
    EXPECT_CALL( mockMinimax , getMovesList( true ) )
    .WillOnce( testing::ReturnRef( *mockMoves ) );
    
    int ply = 1;
    ASSERT_EQ( INFINITE, minimax->minimax( ply, -100, +100, true ) );
}

TEST_F( MinimaxTest, MinimaxMaximizePlyReachedTest ) {
    bool maximaze = true;
    EXPECT_CALL( mockMinimax , getStaticEvaluation() )
    .WillOnce( Return( 10 ) );
    
    moves.push_back( new MockOption );
    mockMoves->setMovementsVector( moves );
    
    EXPECT_CALL( mockMinimax , getMovesList( maximaze ) )
    .WillOnce( testing::ReturnRef( *mockMoves ) );
    
    EXPECT_CALL( mockMinimax, minimaxMax( testing::_, 10, testing::_,
                                          testing::_, testing::_ ) )
    .WillOnce( testing::Return( 20 ) );
    
    int ply = 1;
    
    ASSERT_EQ( 20, minimax->minimax( ply, -100, +100, maximaze ) );
}

TEST_F( MinimaxTest, MinimaxMinimizePlyReachedTest ) {
    bool maximaze = false;
    EXPECT_CALL( mockMinimax , getStaticEvaluation() )
    .WillOnce( Return( 10 ) );
    
    moves.push_back( new MockOption );
    mockMoves->setMovementsVector( moves );
    
    EXPECT_CALL( mockMinimax , getMovesList( maximaze ) )
    .WillOnce( testing::ReturnRef( *mockMoves ) );
    
    EXPECT_CALL( mockMinimax, minimaxMin( testing::_, 10 ) )
    .WillOnce( testing::Return( 20 ) );
    
    int ply = 1;
    
    ASSERT_EQ( 20, minimax->minimax( ply, -100, +100, maximaze ) );
}

TEST_F( MinimaxTest, MinimaxAlphaValueHigherUpdatePrun ) {
    bool maximaze = true;
    
    moves.push_back( new MockOption );
    moves.push_back( new MockOption );
    mockMoves->setMovementsVector( moves );
    
    EXPECT_CALL( mockMinimax , getMovesList( maximaze ) )
    .WillOnce( testing::ReturnRef( *mockMoves ) );
    
    EXPECT_CALL( mockMinimax, minimaxMax( testing::_, testing::_,
                                         testing::_, testing::_, testing::_ ) )
    .WillOnce( testing::Return( 5 ) );
    
    int ply = 1;
    int alpha = 20;
    int beta = 10;
    
    ASSERT_EQ( 5, minimax->minimax( ply, alpha, beta, maximaze ) );
}

//TEST_F( MinimaxTest, MinimaxAlphaValueEqualUpdatePrun ) {
//    bool maximaze = true;
//    
//    moves.push_back( &option );
//    moves.push_back( &option );
//    
//    EXPECT_CALL( mockMinimax , getMovesList( maximaze ) )
//    .WillOnce( testing::Return( moves ) );
//    
//    EXPECT_CALL( mockMinimax, minimaxMax( testing::_, testing::_,
//                                         testing::_, testing::_, testing::_ ) )
//    .WillOnce( testing::Return( 5 ) );
//    
//    int ply = 1;
//    int alpha = 20;
//    int beta = 20;
//    
//    ASSERT_EQ( 5, minimax->minimax( ply, alpha, beta, maximaze ) );
//}
//
//TEST_F( MinimaxTest, MinimaxBetaValueUpdatePrun ) {
//    bool maximaze = false;
//    
//    moves.push_back( &option );
//    moves.push_back( &option );
//    
//    EXPECT_CALL( mockMinimax , getMovesList( maximaze ) )
//    .WillOnce( testing::Return( moves ) );
//    
//    EXPECT_CALL( mockMinimax, minimaxMin( testing::_, testing::_ ) )
//    .WillOnce( testing::Return( 25 ) );
//    
//    int ply = 1;
//    int alpha = 20;
//    int beta = 10;
//    
//    ASSERT_EQ( 25, minimax->minimax( ply, alpha, beta, maximaze ) );
//}
//
//TEST_F( MinimaxTest, MinimaxMinimazePunedAvoided ) {
//    bool maximaze = false;
//    
//    moves.push_back( &option );
//    moves.push_back( &option );
//    
//    EXPECT_CALL( mockMinimax , getMovesList( maximaze ) )
//    .WillOnce( testing::Return( moves ) );
//    
//    EXPECT_CALL( mockMinimax, minimaxMin( testing::_, testing::_ ) )
//    .Times( 2 )
//    .WillOnce( testing::Return( 20 ) )
//    .WillOnce( testing::Return( 30 ) );
//    
//    int ply = 1;
//    int alpha = 5;
//    int beta = 10;
//    
//    ASSERT_EQ( 30, minimax->minimax( ply, alpha, beta, maximaze ) );
//}
//
//TEST_F( MinimaxTest, MinimaxMaximizePunedAvoided ) {
//    bool maximaze = true;
//    
//    moves.push_back( &option );
//    moves.push_back( &option );
//    
//    EXPECT_CALL( mockMinimax , getMovesList( maximaze ) )
//    .WillOnce( testing::Return( moves ) );
//    
//    EXPECT_CALL( mockMinimax, minimaxMax( testing::_, testing::_,
//                                          testing::_, testing::_, testing::_ ) )
//    .Times( 2 )
//    .WillOnce( testing::Return( 20 ) )
//    .WillOnce( testing::Return( 30 ) );
//    
//    int ply = 1;
//    int alpha = 40;
//    int beta = 50;
//    
//    ASSERT_EQ( 30, minimax->minimax( ply, alpha, beta, maximaze ) );
//}
//
//TEST_F( MinimaxTest, MinimaxLoggerTestPly1 ) {
//    bool maximaze = true;
//    minimax = new MinimaxAlgorithm( &mockMinimax );
//    minimax->setDebugLogger( new DotBuilder );
//    
//    moves.push_back( &option );
//    moves.push_back( &option );
//    
//    EXPECT_CALL( mockMinimax , getMovesList( testing::_ ) )
//    .WillOnce( testing::Return( moves ) );
//    
//    int ply = 1;
//    int alpha = 40;
//    int beta = 50;
//
//    minimax->minimax( ply, alpha, beta, maximaze );
//    ASSERT_EQ( "0--1\n0--3\n", minimax->getGraphLog() );
//}
//
//TEST_F( MinimaxTest, MinimaxPly2IterationTest ) {
//    bool maximaze = true;
//    
//    moves.push_back( &option );
//    moves.push_back( &option );
//    
//    std::vector<Option*> moves1;
//    std::vector<Option*> moves3;
//    
//    moves1.push_back( &option );
//    
//    moves3.push_back( &option );
//    moves3.push_back( &option );
//    moves3.push_back( &option );
//    
//    EXPECT_CALL( mockMinimax, minimaxMax( testing::_, testing::_,
//                                         testing::_, testing::_, testing::_ ) )
//    .Times( 2 )
//    .WillRepeatedly( testing::Return( 20 ) );
//    
//    EXPECT_CALL( mockMinimax, minimaxMin( testing::_, testing::_ ) )
//    .Times( 4 )
//    .WillRepeatedly( testing::Return( 50 ) );
//    
//    EXPECT_CALL( mockMinimax , getMovesList( testing::_ ) )
//    .Times( 3 )
//    .WillOnce( testing::Return( moves ) )
//    .WillOnce( testing::Return( moves1 ) )
//    .WillOnce( testing::Return( moves3 ) );
//    
//    int ply = 2;
//    int alpha = 40;
//    int beta = 50;
//    minimax->setDebugLogger( new DotBuilder );
//    minimax->minimax( ply, alpha, beta, maximaze );
//    ASSERT_EQ( "0--1--2\n1--0--5--6\n5--8\n5--10\n" ,
//              minimax->getGraphLog() );
//}
//
//TEST_F( MinimaxTest, MinimaxPly2PruneIterationTest ) {
//    bool maximaze = true;
//    
//    moves.push_back( &option );
//    moves.push_back( &option );
//    
//    std::vector<Option*> moves1;
//    std::vector<Option*> moves3;
//    
//    moves1.push_back( &option );
//    
//    moves3.push_back( &option );
//    moves3.push_back( &option );
//    moves3.push_back( &option );
//    
//    EXPECT_CALL( mockMinimax, minimaxMax( testing::_, testing::_,
//                                         testing::_, testing::_, testing::_ ) )
//    .Times( 2 )
//    .WillRepeatedly( testing::Return( 20 ) );
//    
//    EXPECT_CALL( mockMinimax, minimaxMin( testing::_, testing::_ ) )
//    .Times( 2 )
//    .WillOnce( testing::Return( 50 ) )
//    .WillOnce( testing::Return( 20 ) );
//    
//    EXPECT_CALL( mockMinimax , getMovesList( testing::_ ) )
//    .Times( 3 )
//    .WillOnce( testing::Return( moves ) )
//    .WillOnce( testing::Return( moves1 ) )
//    .WillOnce( testing::Return( moves3 ) );
//    
//    int ply = 2;
//    int alpha = 40;
//    int beta = 50;
//    minimax->setDebugLogger( new DotBuilder );
//    minimax->minimax( ply, alpha, beta, maximaze );
//    std::cout << minimax->getGraphLog() << std::endl;
//    ASSERT_EQ( "0--1--2\n1--0--5--6\n" ,
//               minimax->getGraphLog() );
//}
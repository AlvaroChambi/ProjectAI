//
//  HeuristicTest.cpp
//  ProjectWar
//
//  Created by Pablo Luis Gutierrez on 02/06/16.
//  Copyright © 2016 Alvaro Chambi Campos. All rights reserved.
//

#include <stdio.h>
#include "HeuristicFunction.h"
#include "MockPlayer.h"
#include "MockMap.h"

#include "gtest/gtest.h"

class HeuristicTest : public ::testing::Test {
public:
    int DRAW_VALUE = 0;
    int WIN_VALUE = 10000;
    int LOST_VALUE = -10000;
    int NOT_FINISHED = 0;
    
    HeuristicTest() {
        
    }
    
    virtual void SetUp() {
    }
    
    virtual void TearDown() {
    }
    
    MockPlayer player;
    MockPlayer enemy;
    MockMap map;
    HeuristicFunction heuristic;
};

TEST_F( HeuristicTest, GameOverScoreUnfinished ) {
    EXPECT_CALL( player , hasUnitAlive() )
    .WillOnce( testing::Return( true ) );
    EXPECT_CALL( player , hasCapturedHQ( testing::_ ) )
    .WillOnce( testing::Return( false ) );
    
    EXPECT_CALL( enemy , hasUnitAlive() )
    .WillOnce( testing::Return( true ) );
    EXPECT_CALL( enemy , hasCapturedHQ( testing::_ ) )
    .WillOnce( testing::Return( false ) );
    
    int result = heuristic.getGameOverScore( (Player&)player,
                                             (Player&)enemy );
    
    ASSERT_EQ( NOT_FINISHED , result );
}

TEST_F( HeuristicTest, GameOverScoreLostDeadUnits ) {
    EXPECT_CALL( player , hasUnitAlive() )
    .WillOnce( testing::Return( false ) );
    EXPECT_CALL( player , hasCapturedHQ( testing::_ ) )
    .WillOnce( testing::Return( false ) );
    
    EXPECT_CALL( enemy , hasUnitAlive() )
    .WillOnce( testing::Return( true ) );
    EXPECT_CALL( enemy , hasCapturedHQ( testing::_ ) )
    .WillOnce( testing::Return( false ) );
    
    int result = heuristic.getGameOverScore( (Player&)player,
                                             (Player&)enemy );
    
    ASSERT_EQ( LOST_VALUE , result );
}

TEST_F( HeuristicTest, GameOverScoreLostHQCaptured ) {
    EXPECT_CALL( player , hasUnitAlive() )
    .WillOnce( testing::Return( true ) );
    EXPECT_CALL( player , hasCapturedHQ( testing::_ ) )
    .WillOnce( testing::Return( false ) );
    
    EXPECT_CALL( enemy , hasUnitAlive() )
    .WillOnce( testing::Return( true ) );
    EXPECT_CALL( enemy , hasCapturedHQ( testing::_ ) )
    .WillOnce( testing::Return( true ) );
    
    int result = heuristic.getGameOverScore( (Player&)player,
                                             (Player&)enemy );
    
    ASSERT_EQ( LOST_VALUE , result );
}

TEST_F( HeuristicTest, GameOverScoreWinDeadUnits ) {
    EXPECT_CALL( player , hasUnitAlive() )
    .WillOnce( testing::Return( true ) );
    EXPECT_CALL( player , hasCapturedHQ( testing::_ ) )
    .WillOnce( testing::Return( false ) );
    
    EXPECT_CALL( enemy , hasUnitAlive() )
    .WillOnce( testing::Return( false ) );
    EXPECT_CALL( enemy , hasCapturedHQ( testing::_ ) )
    .WillOnce( testing::Return( false ) );
    
    int result = heuristic.getGameOverScore( (Player&)player,
                                             (Player&)enemy );
    
    ASSERT_EQ( WIN_VALUE , result );
}

TEST_F( HeuristicTest, GameOverScoreWinHQCaptured ) {
    EXPECT_CALL( player , hasUnitAlive() )
    .WillOnce( testing::Return( true ) );
    EXPECT_CALL( player , hasCapturedHQ( testing::_ ) )
    .WillOnce( testing::Return( true ) );
    
    EXPECT_CALL( enemy , hasUnitAlive() )
    .WillOnce( testing::Return( true ) );
    EXPECT_CALL( enemy , hasCapturedHQ( testing::_ ) )
    .WillOnce( testing::Return( false ) );
    
    int result = heuristic.getGameOverScore( (Player&)player,
                                             (Player&)enemy );
    
    ASSERT_EQ( WIN_VALUE , result );
}

TEST_F( HeuristicTest, GameOverScoreAllUnitsDead ) {
    EXPECT_CALL( player , hasUnitAlive() )
    .WillOnce( testing::Return( false ) );
    EXPECT_CALL( player , hasCapturedHQ( testing::_ ) )
    .WillOnce( testing::Return( false ) );
    
    EXPECT_CALL( enemy , hasUnitAlive() )
    .WillOnce( testing::Return( false ) );
    EXPECT_CALL( enemy , hasCapturedHQ( testing::_ ) )
    .WillOnce( testing::Return( false ) );
    
    ASSERT_ANY_THROW( heuristic.getGameOverScore( (Player&)player,
                                                  (Player&)enemy ) );
}

TEST_F( HeuristicTest, GameOverScoreBothHQCaptured ) {
    EXPECT_CALL( player , hasUnitAlive() )
    .WillOnce( testing::Return( true ) );
    EXPECT_CALL( player , hasCapturedHQ( testing::_ ) )
    .WillOnce( testing::Return( true ) );
    
    EXPECT_CALL( enemy , hasUnitAlive() )
    .WillOnce( testing::Return( true ) );
    EXPECT_CALL( enemy , hasCapturedHQ( testing::_ ) )
    .WillOnce( testing::Return( true ) );
    
    ASSERT_ANY_THROW( heuristic.getGameOverScore( (Player&)player,
                                                  (Player&)enemy ) );
}

TEST_F( HeuristicTest, GameOverScoreLostUnitsDead ) {
    EXPECT_CALL( player , hasUnitAlive() )
    .WillOnce( testing::Return( false ) );
    EXPECT_CALL( player , hasCapturedHQ( testing::_ ) )
    .WillOnce( testing::Return( false ) );
    
    EXPECT_CALL( enemy , hasUnitAlive() )
    .WillOnce( testing::Return( false ) );
    EXPECT_CALL( enemy , hasCapturedHQ( testing::_ ) )
    .WillOnce( testing::Return( true ) );
    
    ASSERT_ANY_THROW( heuristic.getGameOverScore( (Player&)player,
                                                  (Player&)enemy ) );
}

TEST_F( HeuristicTest, GameOverScoreWinUnitsDead ) {
    EXPECT_CALL( player , hasUnitAlive() )
    .WillOnce( testing::Return( false ) );
    EXPECT_CALL( player , hasCapturedHQ( testing::_ ) )
    .WillOnce( testing::Return( true ) );
    
    EXPECT_CALL( enemy , hasUnitAlive() )
    .WillOnce( testing::Return( false ) );
    EXPECT_CALL( enemy , hasCapturedHQ( testing::_ ) )
    .WillOnce( testing::Return( false ) );
    
    ASSERT_ANY_THROW( heuristic.getGameOverScore( (Player&)player,
                                                  (Player&)enemy ) );
}
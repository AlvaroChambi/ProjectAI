//
//  GameStateTest.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 30/5/16.
//  Copyright © 2016 Alvaro Chambi Campos. All rights reserved.
//
#include "gtest/gtest.h"

#include "GameState.h"
#include "MockPlayer.h"
#include "GameException.h"

class GameStateTest : public ::testing::Test {
public:
    GameStateTest() {
        gameState = new GameState( &player, &enemy );
    }
    
    virtual void SetUp() {

    }
    
    virtual void TearDown() {
        
    }
    
    GameState* gameState;
    MockPlayer player;
    MockPlayer enemy;
};

TEST_F( GameStateTest, GameOverScoreUnfinished ) {
    EXPECT_CALL( player , hasUnitAlive() )
    .WillOnce( testing::Return( true ) );
    EXPECT_CALL( player , hasCapturedHQ() )
    .WillOnce( testing::Return( false ) );
    
    EXPECT_CALL( enemy , hasUnitAlive() )
    .WillOnce( testing::Return( true ) );
    EXPECT_CALL( enemy , hasCapturedHQ() )
    .WillOnce( testing::Return( false ) );
    
    int result = gameState->getGameOverScore();
    
    ASSERT_EQ( GameState::NOT_FINISHED , result );
}

TEST_F( GameStateTest, GameOverScoreLostDeadUnits ) {
    EXPECT_CALL( player , hasUnitAlive() )
    .WillOnce( testing::Return( false ) );
    EXPECT_CALL( player , hasCapturedHQ() )
    .WillOnce( testing::Return( false ) );
    
    EXPECT_CALL( enemy , hasUnitAlive() )
    .WillOnce( testing::Return( true ) );
    EXPECT_CALL( enemy , hasCapturedHQ() )
    .WillOnce( testing::Return( false ) );
    
    int result = gameState->getGameOverScore();
    
    ASSERT_EQ( GameState::LOST_VALUE , result );
}

TEST_F( GameStateTest, GameOverScoreLostHQCaptured ) {
    EXPECT_CALL( player , hasUnitAlive() )
    .WillOnce( testing::Return( true ) );
    EXPECT_CALL( player , hasCapturedHQ() )
    .WillOnce( testing::Return( false ) );
    
    EXPECT_CALL( enemy , hasUnitAlive() )
    .WillOnce( testing::Return( true ) );
    EXPECT_CALL( enemy , hasCapturedHQ() )
    .WillOnce( testing::Return( true ) );
    
    int result = gameState->getGameOverScore();
    
    ASSERT_EQ( GameState::LOST_VALUE , result );
}

TEST_F( GameStateTest, GameOverScoreWinDeadUnits ) {
    EXPECT_CALL( player , hasUnitAlive() )
    .WillOnce( testing::Return( true ) );
    EXPECT_CALL( player , hasCapturedHQ() )
    .WillOnce( testing::Return( false ) );
    
    EXPECT_CALL( enemy , hasUnitAlive() )
    .WillOnce( testing::Return( false ) );
    EXPECT_CALL( enemy , hasCapturedHQ() )
    .WillOnce( testing::Return( false ) );
    
    int result = gameState->getGameOverScore();
    
    ASSERT_EQ( GameState::WIN_VALUE , result );
}

TEST_F( GameStateTest, GameOverScoreWinHQCaptured ) {
    EXPECT_CALL( player , hasUnitAlive() )
    .WillOnce( testing::Return( true ) );
    EXPECT_CALL( player , hasCapturedHQ() )
    .WillOnce( testing::Return( true ) );
    
    EXPECT_CALL( enemy , hasUnitAlive() )
    .WillOnce( testing::Return( true ) );
    EXPECT_CALL( enemy , hasCapturedHQ() )
    .WillOnce( testing::Return( false ) );
    
    int result = gameState->getGameOverScore();
    
    ASSERT_EQ( GameState::WIN_VALUE , result );
}

TEST_F( GameStateTest, GameOverScoreAllUnitsDead ) {
    EXPECT_CALL( player , hasUnitAlive() )
    .WillOnce( testing::Return( false ) );
    EXPECT_CALL( player , hasCapturedHQ() )
    .WillOnce( testing::Return( false ) );
    
    EXPECT_CALL( enemy , hasUnitAlive() )
    .WillOnce( testing::Return( false ) );
    EXPECT_CALL( enemy , hasCapturedHQ() )
    .WillOnce( testing::Return( false ) );
    
    ASSERT_ANY_THROW( gameState->getGameOverScore() );
}

TEST_F( GameStateTest, GameOverScoreBothHQCaptured ) {
    EXPECT_CALL( player , hasUnitAlive() )
    .WillOnce( testing::Return( true ) );
    EXPECT_CALL( player , hasCapturedHQ() )
    .WillOnce( testing::Return( true ) );
    
    EXPECT_CALL( enemy , hasUnitAlive() )
    .WillOnce( testing::Return( true ) );
    EXPECT_CALL( enemy , hasCapturedHQ() )
    .WillOnce( testing::Return( true ) );
    
    ASSERT_ANY_THROW( gameState->getGameOverScore() );
}

TEST_F( GameStateTest, GameOverScoreLostUnitsDead ) {
    EXPECT_CALL( player , hasUnitAlive() )
    .WillOnce( testing::Return( false ) );
    EXPECT_CALL( player , hasCapturedHQ() )
    .WillOnce( testing::Return( false ) );
    
    EXPECT_CALL( enemy , hasUnitAlive() )
    .WillOnce( testing::Return( false ) );
    EXPECT_CALL( enemy , hasCapturedHQ() )
    .WillOnce( testing::Return( true ) );
    
    ASSERT_ANY_THROW( gameState->getGameOverScore() );
}

TEST_F( GameStateTest, GameOverScoreWinUnitsDead ) {
    EXPECT_CALL( player , hasUnitAlive() )
    .WillOnce( testing::Return( false ) );
    EXPECT_CALL( player , hasCapturedHQ() )
    .WillOnce( testing::Return( true ) );
    
    EXPECT_CALL( enemy , hasUnitAlive() )
    .WillOnce( testing::Return( false ) );
    EXPECT_CALL( enemy , hasCapturedHQ() )
    .WillOnce( testing::Return( false ) );
    
    ASSERT_ANY_THROW( gameState->getGameOverScore() );
}
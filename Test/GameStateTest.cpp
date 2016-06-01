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
#include "MockMap.h"
#include "GameException.h"

class GameStateTest : public ::testing::Test {
public:
    GameStateTest() {
        gameState = new GameState( &player, &enemy, &map );
    }
    
    virtual void SetUp() {

    }
    
    virtual void TearDown() {
        
    }
    
    GameState* gameState;
    MockPlayer player;
    MockPlayer enemy;
    MockMap map;
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

TEST_F( GameStateTest, GetUnitMoveCommands ) {
    Unit* unit = new Unit;
    unit->setPosition( 1 , 1 );
    unit->setMovement( 2 );
    
    EXPECT_CALL( map , isOnBounds( testing::_ ) )
    .WillOnce( testing::Return( true ) );
    
    EXPECT_CALL( map , isValidPosition( testing::_ ) )
    .Times( 9 )
    .WillRepeatedly( testing::Return( true ) );
    
    std::pair<Point, Point>* boundingArea = new std::pair<Point, Point>;
    boundingArea->first = Point( 0, 0 );
    boundingArea->second = Point( 3, 3 );
    
    EXPECT_CALL( map , getBoundingArea( testing::_, testing::_ ) )
    .WillOnce( testing::Return( boundingArea ) );
    
    std::vector<Option*>* moves = gameState->getUnitMoveCommands( unit );
    ASSERT_EQ( 9 , moves->size() );
}

TEST_F( GameStateTest, GetUnitMoveCommandsDestinationInvalid ) {
    Unit* unit = new Unit;
    unit->setPosition( 1 , 1 );
    unit->setMovement( 2 );
    
    EXPECT_CALL( map , isOnBounds( testing::_ ) )
    .WillOnce( testing::Return( true ) );
    
    EXPECT_CALL( map , isValidPosition( testing::_ ) )
    .Times( 9 )
    .WillOnce( testing::Return( false ) )
    .WillRepeatedly( testing::Return( true ) );
    
    std::pair<Point, Point>* boundingArea = new std::pair<Point, Point>;
    boundingArea->first = Point( 0, 0 );
    boundingArea->second = Point( 3, 3 );
    
    EXPECT_CALL( map , getBoundingArea( testing::_, testing::_ ) )
    .WillOnce( testing::Return( boundingArea ) );
    
    std::vector<Option*>* moves = gameState->getUnitMoveCommands( unit );
    ASSERT_EQ( 8 , moves->size() );
}

TEST_F( GameStateTest, GetUnitMoveCommandsUnitOutOfBounds ) {
    Unit* unit = new Unit;
    EXPECT_CALL( map , isOnBounds( testing::_ ) )
    .WillOnce( testing::Return( false ) );
    ASSERT_ANY_THROW( gameState->getUnitMoveCommands( unit ) );
}
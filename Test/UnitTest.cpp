//
//  UnitTest.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 1/6/16.
//  Copyright © 2016 Alvaro Chambi Campos. All rights reserved.
//

#include "Unit.h"
#include "gtest/gtest.h"
#include "MockMap.h"

class UnitTest : public ::testing::Test {
public:
    UnitTest() {
    }
    
    virtual void SetUp() {
        unit = new Unit;
    }
    
    virtual void TearDown() {
    }
    
    Unit* unit;
    MockMap map;
};

TEST_F( UnitTest, getMoveActionsTest ) {
    unit->setPosition( 1 , 1 );
    unit->setMovement( 2 );
    
    EXPECT_CALL( map , isOnBounds( testing::_ ) )
    .WillOnce( testing::Return( true ) );
    
    EXPECT_CALL( map , isValidPosition( testing::_ ) )
    .Times( 9 )
    .WillRepeatedly( testing::Return( true ) );
    
    EXPECT_CALL( map, getTile( testing::_, testing::_ ) )
    .Times( 9 )
    .WillRepeatedly( testing::Return( Tile() ) );
    
    std::pair<Point, Point>* boundingArea = new std::pair<Point, Point>;
    boundingArea->first = Point( 0, 0 );
    boundingArea->second = Point( 3, 3 );
    
    EXPECT_CALL( map , getBoundingArea( testing::_, testing::_ ) )
    .WillOnce( testing::Return( boundingArea ) );
    
    std::vector<Action*>* actions = unit->getMoveActions( &map );
    ASSERT_EQ( 9 , actions->size() );
}

TEST_F( UnitTest, GetMoveActionsDestinationInvalid ) {
    unit->setPosition( 1 , 1 );
    unit->setMovement( 2 );
    
    EXPECT_CALL( map , isOnBounds( testing::_ ) )
    .WillOnce( testing::Return( true ) );
    
    EXPECT_CALL( map , isValidPosition( testing::_ ) )
    .Times( 9 )
    .WillOnce( testing::Return( false ) )
    .WillRepeatedly( testing::Return( true ) );
    
    EXPECT_CALL( map, getTile( testing::_, testing::_ ) )
    .Times( 8 )
    .WillRepeatedly( testing::Return( Tile() ) );
    
    std::pair<Point, Point>* boundingArea = new std::pair<Point, Point>;
    boundingArea->first = Point( 0, 0 );
    boundingArea->second = Point( 3, 3 );
    
    EXPECT_CALL( map , getBoundingArea( testing::_, testing::_ ) )
    .WillOnce( testing::Return( boundingArea ) );
    
    std::vector<Action*>* moves = unit->getMoveActions( &map );
    ASSERT_EQ( 8 , moves->size() );
}

TEST_F( UnitTest, GetMoveActionsUnitOutOfBounds ) {
    EXPECT_CALL( map , isOnBounds( testing::_ ) )
    .WillOnce( testing::Return( false ) );
    ASSERT_ANY_THROW( unit->getMoveActions( &map ) );
}
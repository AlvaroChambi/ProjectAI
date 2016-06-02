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
#include "Player.h"

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

TEST_F( UnitTest, getMoveActionsTestFilledBounds ) {
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

TEST_F( UnitTest, getMoveActionsBoundsNotFilled ) {
    unit->setPosition( 1 , 1 );
    unit->setMovement( 1 );
    
    EXPECT_CALL( map , isOnBounds( testing::_ ) )
    .WillOnce( testing::Return( true ) );
    
    EXPECT_CALL( map , isValidPosition( testing::_ ) )
    .Times( 9 )
    .WillRepeatedly( testing::Return( true ) );
    
    EXPECT_CALL( map, getTile( testing::_, testing::_ ) )
    .Times( 5 )
    .WillRepeatedly( testing::Return( Tile() ) );
    
    std::pair<Point, Point>* boundingArea = new std::pair<Point, Point>;
    boundingArea->first = Point( 0, 0 );
    boundingArea->second = Point( 3, 3 );
    
    EXPECT_CALL( map , getBoundingArea( testing::_, testing::_ ) )
    .WillOnce( testing::Return( boundingArea ) );
    
    std::vector<Action*>* actions = unit->getMoveActions( &map );
    ASSERT_EQ( 5 , actions->size() );
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

TEST_F( UnitTest, GetAttackActionsTest ) {
    unit->setPosition( 2 , 1 );
    unit->setMovement( 2 );
    unit->setAttackRange( 1 );
    
    std::vector<Unit*> targets;
    Unit* target0 = new Unit;
    target0->setPosition( 1, 1 );
    targets.push_back( target0 );
    
    EXPECT_CALL( map , isOnBounds( testing::_ ) )
    .WillOnce( testing::Return( true ) );
    
    EXPECT_CALL( map , isValidPosition( testing::_ ) )
    .Times( 9 )
    .WillRepeatedly( testing::Return( true ) );
    
    EXPECT_CALL( map, getTile( testing::_, testing::_ ) )
    .Times( 5 )
    .WillRepeatedly( testing::Return( Tile() ) );
    
    std::pair<Point, Point>* boundingArea = new std::pair<Point, Point>;
    boundingArea->first = Point( 0, 0 );
    boundingArea->second = Point( 3, 3 );
    
    EXPECT_CALL( map , getBoundingArea( testing::_, testing::_ ) )
    .WillOnce( testing::Return( boundingArea ) );
    
    std::vector<Action*>* moves = unit->getAttackActions( &map, targets );
    ASSERT_EQ( 5 , moves->size() );
}

TEST_F( UnitTest, GetAttackActionsReachLimit ) {
    unit->setPosition( 2 , 1 );
    unit->setMovement( 1 );
    unit->setAttackRange( 1 );
    
    std::vector<Unit*> targets;
    Unit* target0 = new Unit;
    target0->setPosition( 0, 1 );
    targets.push_back( target0 );
    
    EXPECT_CALL( map , isOnBounds( testing::_ ) )
    .WillOnce( testing::Return( true ) );
    
    EXPECT_CALL( map , isValidPosition( testing::_ ) )
    .Times( 9 )
    .WillRepeatedly( testing::Return( true ) );
    
    EXPECT_CALL( map, getTile( testing::_, testing::_ ) )
    .Times( 1 )
    .WillRepeatedly( testing::Return( Tile() ) );
    
    std::pair<Point, Point>* boundingArea = new std::pair<Point, Point>;
    boundingArea->first = Point( 0, 0 );
    boundingArea->second = Point( 3, 3 );
    
    EXPECT_CALL( map , getBoundingArea( testing::_, testing::_ ) )
    .WillOnce( testing::Return( boundingArea ) );
    
    std::vector<Action*>* moves = unit->getAttackActions( &map, targets );
    ASSERT_EQ( 1 , moves->size() );
}

TEST_F( UnitTest, GetAttackActionsCannotReach ) {
    unit->setPosition( 2 , 1 );
    unit->setMovement( 1 );
    unit->setAttackRange( 1 );
    
    std::vector<Unit*> targets;
    Unit* target0 = new Unit;
    target0->setPosition( 0, 0 );
    targets.push_back( target0 );
    
    EXPECT_CALL( map , isOnBounds( testing::_ ) )
    .WillOnce( testing::Return( true ) );
    
    std::vector<Action*>* moves = unit->getAttackActions( &map, targets );
    ASSERT_TRUE( moves->empty() );
}

TEST_F( UnitTest, GetCaptureActionsOpponentBuilding ) {
    unit->setPosition( 2 , 1 );
    unit->setMovement( 2 );
    
    Building* building = new Building;
    Tile tile = Tile();
    tile.position = Point( 0, 1 );
    building->setPosition( tile );
    building->setOwnerID( 0 );
    
    std::vector<Building*> buildings;
    buildings.push_back( building );
    
    Player* player = new Player( 1 );
    
    
    EXPECT_CALL( map , isOnBounds( testing::_ ) )
    .WillOnce( testing::Return( true ) );
    
    EXPECT_CALL( map, getTile( testing::_, testing::_ ) )
    .Times( 1 )
    .WillRepeatedly( testing::Return( Tile() ) );
    
    std::vector<Action*>* moves = unit->getCaptureActions( &map, player,
                                                           buildings );
    ASSERT_EQ( 1 , moves->size() );
}

TEST_F( UnitTest, GetCaptureActionsOwnBuilding ) {
    unit->setPosition( 2 , 1 );
    unit->setMovement( 2 );
    
    Building* building = new Building;
    Tile tile = Tile();
    tile.position = Point( 0, 1 );
    building->setPosition( tile );
    building->setOwnerID( 1 );
    
    std::vector<Building*> buildings;
    buildings.push_back( building );
    
    Player* player = new Player( 1 );
    
    
    EXPECT_CALL( map , isOnBounds( testing::_ ) )
    .WillOnce( testing::Return( true ) );
    
    std::vector<Action*>* moves = unit->getCaptureActions( &map, player,
                                                          buildings );
    ASSERT_EQ( 0 , moves->size() );
}
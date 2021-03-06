//
//  ActionsProviderTest.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 13/07/16.
//  Copyright (c) 2016 Alvaro Chambi Campos. All rights reserved.
//

#include <iostream>
#include "ActionsProvider.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "MockMap.h"
#include "MockEvaluator.h"

#include "MoveCommand.h"

class ActionsProviderTest : public ::testing::Test {
public:
    ActionsProviderTest() {
        actionsProvider = new ActionsProvider( mockContext );
    }
    
    virtual void SetUp() {
    }
    
    virtual void TearDown() {
        
    }
    
    ActionsProvider* actionsProvider;
    MockMap mockContext;
};

TEST_F( ActionsProviderTest, getTileEmptyUnavailableTile ) {
    Point position( 0, 2 );
    Unit unit;
    unit.setid( 0 );
    unit.setMovement( 1 );
    unit.setAttackRange( 1 );
    unit.setPosition( 0, 0 );
    
    EXPECT_CALL( mockContext, getEntity( 0 ) )
    .WillOnce( testing::Return( &unit ) );
    
    TargetTile tile = actionsProvider->getTargetTileForPosition( 0,
                                                                position );
    ASSERT_EQ( TARGET_NOT_AVAILABLE, tile );
}

TEST_F( ActionsProviderTest, getTileEmptyAvailableTile ) {
    Point position( 0, 1 );
    Unit unit;
    unit.setid( 0 );
    unit.setMovement( 1 );
    unit.setAttackRange( 1 );
    unit.setPosition( 0, 0 );
    
    EXPECT_CALL( mockContext, getEntity( 0 ) )
    .WillOnce( testing::Return( &unit ) );
    
    TargetTile tile = actionsProvider->getTargetTileForPosition( 0,
                                                                position );
    ASSERT_EQ( TARGET_POSITION, tile );
}

TEST_F( ActionsProviderTest, getTileOwnEntityUnavailableTile ) {
    Point position( 0, 2 );
    
    Unit unit;
    unit.setOwnerID( 0 );
    unit.setid( 0 );
    unit.setMovement( 1 );
    unit.setAttackRange( 1 );
    unit.setPosition( 0, 0 );
    
    Unit entity;
    entity.setOwnerID( 0 );
    
    EXPECT_CALL( mockContext, getEntity( 0 ) )
    .WillOnce( testing::Return( &unit ) );
    
    EXPECT_CALL( mockContext, getEntity( position ) )
    .WillOnce( testing::Return( &entity ) );
    
    TargetTile tile = actionsProvider->getTargetTileForPosition( 0,
                                                                position );
    ASSERT_EQ( TARGET_NOT_AVAILABLE, tile );
}

TEST_F( ActionsProviderTest, getTileOwnEntityAvailableTile ) {
    Point position( 0, 1 );
    
    Unit unit;
    unit.setOwnerID( 0 );
    unit.setid( 0 );
    unit.setMovement( 1 );
    unit.setAttackRange( 1 );
    unit.setPosition( 0, 0 );
    
    Unit entity;
    entity.setOwnerID( 0 );
    entity.setid( 1 );
    
    EXPECT_CALL( mockContext, getEntity( 0 ) )
    .WillOnce( testing::Return( &unit ) );
    
    EXPECT_CALL( mockContext, getEntity( position ) )
    .WillOnce( testing::Return( &entity ) );
    
    TargetTile tile = actionsProvider->getTargetTileForPosition( 0,
                                                                position );
    ASSERT_EQ( TARGET_NOT_AVAILABLE, tile );
}

TEST_F( ActionsProviderTest, getTileOwnPosition ) {
    Point position( 0, 1 );
    
    Unit unit;
    unit.setOwnerID( 0 );
    unit.setid( 0 );
    unit.setMovement( 1 );
    unit.setAttackRange( 1 );
    unit.setPosition( 0, 0 );
    
    EXPECT_CALL( mockContext, getEntity( 0 ) )
    .WillOnce( testing::Return( &unit ) );
    
    EXPECT_CALL( mockContext, getEntity( position ) )
    .WillOnce( testing::Return( &unit ) );
    
    TargetTile tile = actionsProvider->getTargetTileForPosition( 0,
                                                                position );
    
    ASSERT_EQ( TARGET_POSITION, tile );
}

TEST_F( ActionsProviderTest, getTileOpponentEntityUnavailableTile ) {
    Point position( 0, 2 );
    
    Unit unit;
    unit.setOwnerID( 0 );
    unit.setid( 0 );
    unit.setMovement( 1 );
    unit.setAttackRange( 1 );
    unit.setPosition( 0, 0 );
    
    Unit entity;
    entity.setOwnerID( 1 );
    
    EXPECT_CALL( mockContext, getEntity( 0 ) )
    .WillOnce( testing::Return( &unit ) );
    
    EXPECT_CALL( mockContext, getEntity( position ) )
    .WillOnce( testing::Return( &entity ) );
    
    TargetTile tile = actionsProvider->getTargetTileForPosition( 0,
                                                                position );
    ASSERT_EQ( TARGET_ENTITY, tile );
}

TEST_F( ActionsProviderTest, getTileOpponentEntityAvailableTile ) {
    Point position( 0, 1 );
    
    Unit unit;
    unit.setOwnerID( 0 );
    unit.setid( 0 );
    unit.setMovement( 1 );
    unit.setAttackRange( 1 );
    unit.setPosition( 0, 0 );
    
    Unit entity;
    entity.setOwnerID( 1 );
    
    EXPECT_CALL( mockContext, getEntity( 0 ) )
    .WillOnce( testing::Return( &unit ) );
    
    EXPECT_CALL( mockContext, getEntity( position ) )
    .WillOnce( testing::Return( &entity ) );
    
    TargetTile tile = actionsProvider->getTargetTileForPosition( 0,
                                                                position );
    ASSERT_EQ( TARGET_ENTITY, tile );
}

TEST_F( ActionsProviderTest, getTileOwnStructureUnavailableTile ) {
    Point position( 0, 2 );
    
    Unit unit;
    unit.setOwnerID( 0 );
    unit.setid( 0 );
    unit.setMovement( 1 );
    unit.setAttackRange( 1 );
    unit.setPosition( 0, 0 );
    
    Building structure;
    structure.setOwnerID( 0 );
    
    EXPECT_CALL( mockContext, getEntity( 0 ) )
    .WillOnce( testing::Return( &unit ) );
    
    EXPECT_CALL( mockContext, getStructure( position ) )
    .WillOnce( testing::Return( &structure ) );
    
    TargetTile tile = actionsProvider->getTargetTileForPosition( 0,
                                                                position );
    ASSERT_EQ( TARGET_NOT_AVAILABLE, tile );
}

TEST_F( ActionsProviderTest, getTileOwnStructureAvailableTile ) {
    Point position( 0, 1 );
    
    Unit unit;
    unit.setOwnerID( 0 );
    unit.setid( 0 );
    unit.setMovement( 1 );
    unit.setAttackRange( 1 );
    unit.setPosition( 0, 0 );
    
    Building structure;
    structure.setOwnerID( 0 );
    
    EXPECT_CALL( mockContext, getEntity( 0 ) )
    .WillOnce( testing::Return( &unit ) );
    
    EXPECT_CALL( mockContext, getStructure( position ) )
    .WillOnce( testing::Return( &structure ) );
    
    TargetTile tile = actionsProvider->getTargetTileForPosition( 0,
                                                                position );
    ASSERT_EQ( TARGET_POSITION, tile );
}

TEST_F( ActionsProviderTest, getTileOpponentStructureUnavailableTile ) {
    Point position( 0, 2 );
    
    Unit unit;
    unit.setOwnerID( 0 );
    unit.setid( 0 );
    unit.setMovement( 1 );
    unit.setAttackRange( 1 );
    unit.setPosition( 0, 0 );
    
    Building structure;
    structure.setOwnerID( 1 );
    
    EXPECT_CALL( mockContext, getEntity( 0 ) )
    .WillOnce( testing::Return( &unit ) );
    
    EXPECT_CALL( mockContext, getStructure( position ) )
    .WillOnce( testing::Return( &structure ) );
    
    TargetTile tile = actionsProvider->getTargetTileForPosition( 0,
                                                                position );
    ASSERT_EQ( TARGET_NOT_AVAILABLE, tile );
}

TEST_F( ActionsProviderTest, getTileOpponentStructureAvailableTile ) {
    Point position( 0, 1 );
    
    Unit unit;
    unit.setOwnerID( 0 );
    unit.setid( 0 );
    unit.setMovement( 1 );
    unit.setAttackRange( 1 );
    unit.setPosition( 0, 0 );
    
    Building structure;
    structure.setOwnerID( 1 );
    
    EXPECT_CALL( mockContext, getEntity( 0 ) )
    .WillOnce( testing::Return( &unit ) );
    
    EXPECT_CALL( mockContext, getStructure( position ) )
    .WillOnce( testing::Return( &structure ) );
    
    TargetTile tile = actionsProvider->getTargetTileForPosition( 0,
                                                                position );
    ASSERT_EQ( TARGET_STRUCTURE, tile );
}

TEST_F( ActionsProviderTest, getTileOpponentEntityAndStructure ) {
    Point position( 0, 1 );
    
    Unit unit;
    unit.setOwnerID( 0 );
    unit.setid( 0 );
    unit.setMovement( 1 );
    unit.setAttackRange( 1 );
    unit.setPosition( 0, 0 );
    
    Building structure;
    structure.setOwnerID( 1 );
    
    Unit entity;
    entity.setOwnerID( 1 );
    
    EXPECT_CALL( mockContext, getEntity( 0 ) )
    .WillOnce( testing::Return( &unit ) );
    
    EXPECT_CALL( mockContext, getEntity( position ) )
    .WillOnce( testing::Return( &entity ) );
    
    EXPECT_CALL( mockContext, getStructure( position ) )
    .WillOnce( testing::Return( &structure ) );
    
    TargetTile tile = actionsProvider->getTargetTileForPosition( 0,
                                                                position );
    ASSERT_EQ( TARGET_ENTITY, tile );
}

TEST_F( ActionsProviderTest, getTileOwnEntityOpponentStructure ) {
    Point position( 0, 1 );
    
    Unit unit;
    unit.setOwnerID( 0 );
    unit.setid( 0 );
    unit.setMovement( 1 );
    unit.setAttackRange( 1 );
    unit.setPosition( 0, 0 );
    
    Building structure;
    structure.setOwnerID( 1 );
    
    Unit entity;
    entity.setOwnerID( 0 );
    
    EXPECT_CALL( mockContext, getEntity( 0 ) )
    .WillOnce( testing::Return( &unit ) );
    
    EXPECT_CALL( mockContext, getEntity( position ) )
    .WillOnce( testing::Return( &entity ) );
    
    EXPECT_CALL( mockContext, getStructure( position ) )
    .WillOnce( testing::Return( &structure ) );
    
    TargetTile tile = actionsProvider->getTargetTileForPosition( 0,
                                                                position );
    ASSERT_EQ( TARGET_NOT_AVAILABLE, tile );
}

TEST_F( ActionsProviderTest, getTileOwnEntityOwnStructure ) {
    Point position( 0, 1 );
    
    Unit unit;
    unit.setOwnerID( 0 );
    unit.setid( 0 );
    unit.setMovement( 1 );
    unit.setAttackRange( 1 );
    unit.setPosition( 0, 0 );
    
    Building structure;
    structure.setOwnerID( 0 );
    
    Unit entity;
    entity.setOwnerID( 0 );
    
    EXPECT_CALL( mockContext, getEntity( 0 ) )
    .WillOnce( testing::Return( &unit ) );
    
    EXPECT_CALL( mockContext, getEntity( position ) )
    .WillOnce( testing::Return( &entity ) );
    
    EXPECT_CALL( mockContext, getStructure( position ) )
    .WillOnce( testing::Return( &structure ) );
    
    TargetTile tile = actionsProvider->getTargetTileForPosition( 0,
                                                                position );
    ASSERT_EQ( TARGET_NOT_AVAILABLE, tile );
}

TEST_F( ActionsProviderTest, mapVariationsTest ) {
    int numActions = 3;
    std::vector<int> var0 = { 0, 0 };
    std::vector<int> var1 = { 0, 1 };
    std::vector<int> var2 = { 0, 2 };
    
    std::vector<int> var3 = { 1, 0 };
    std::vector<int> var4 = { 1, 1 };
    std::vector<int> var5 = { 1, 2 };
    
    std::vector<int> var6 = { 2, 0 };
    std::vector<int> var7 = { 2, 1 };
    std::vector<int> var8 = { 2, 2 };
    
    std::vector<std::vector<int>> variations = { var0, var1, var2, var3, var4, var5,
                                                 var6, var7, var8 };
    Action* actionA0 = new Action;
    Action* actionA1 = new Action;
    Action* actionA2 = new Action;
    Action* actionB0 = new Action;
    Action* actionB1 = new Action;
    Action* actionB2 = new Action;
    
    std::vector<Action*>* actions =
    new std::vector<Action*> { actionA0, actionA1, actionA2,
                                     actionB0, actionB1, actionB2 };
    MovementsList resultList = actionsProvider->mapVariations( numActions,
                                    variations, *actions );
    std::vector<Option*> result = resultList.getMovementsVector();
    ASSERT_EQ( 9 , (int)result.size() );
    Movement* movement0 = (Movement*)result.at( 0 );
    ASSERT_EQ( actionA0, movement0->getActions().at( 0 ) );
    ASSERT_EQ( actionB0, movement0->getActions().at( 1 ) );
    
    Movement* movement1 = (Movement*)result.at( 1 );
    ASSERT_EQ( actionA0, movement1->getActions().at( 0 ) );
    ASSERT_EQ( actionB1, movement1->getActions().at( 1 ) );
    
    Movement* movement2 = (Movement*)result.at( 2 );
    ASSERT_EQ( actionA0, movement2->getActions().at( 0 ) );
    ASSERT_EQ( actionB2, movement2->getActions().at( 1 ) );
    
    Movement* movement3 = (Movement*)result.at( 3 );
    ASSERT_EQ( actionA1, movement3->getActions().at( 0 ) );
    ASSERT_EQ( actionB0, movement3->getActions().at( 1 ) );
    
    Movement* movement4 = (Movement*)result.at( 4 );
    ASSERT_EQ( actionA1, movement4->getActions().at( 0 ) );
    ASSERT_EQ( actionB1, movement4->getActions().at( 1 ) );
    
    Movement* movement5 = (Movement*)result.at( 5 );
    ASSERT_EQ( actionA1, movement5->getActions().at( 0 ) );
    ASSERT_EQ( actionB2, movement5->getActions().at( 1 ) );
    
    Movement* movement6 = (Movement*)result.at( 6 );
    ASSERT_EQ( actionA2, movement6->getActions().at( 0 ) );
    ASSERT_EQ( actionB0, movement6->getActions().at( 1 ) );
    
    Movement* movement7 = (Movement*)result.at( 7 );
    ASSERT_EQ( actionA2, movement7->getActions().at( 0 ) );
    ASSERT_EQ( actionB1, movement7->getActions().at( 1 ) );
    
    Movement* movement8 = (Movement*)result.at( 8 );
    ASSERT_EQ( actionA2, movement8->getActions().at( 0 ) );
    ASSERT_EQ( actionB2, movement8->getActions().at( 1 ) );
}

TEST_F( ActionsProviderTest, mapVariationsEmptyParamsTest ) {
    int numUnits = 0;
    std::vector<std::vector<int>> variations;
    std::vector<Action*>* actions = new std::vector<Action*>;
    MovementsList result = actionsProvider->mapVariations( numUnits,
                                                    variations, *actions );
    ASSERT_TRUE( result.getMovementsVector().empty() );
}

TEST_F( ActionsProviderTest, mapVariationsInvalidParamsTest ) {
    std::vector<Action*> actions;
    int numUnits = 2;
    
    std::vector<int> var0 = { 0, 0 };
    std::vector<int> var1 = { 0, 1 };
    std::vector<int> var2 = { 1, 0 };
    std::vector<int> var3 = { 1, 1 };
    
    std::vector<std::vector<int>> variations = { var0, var1, var2, var3 };

    ASSERT_ANY_THROW( actionsProvider->mapVariations( numUnits,
                                                      variations, actions ) );
}
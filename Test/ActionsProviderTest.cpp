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
    MapContext mockContext;
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
    
    EXPECT_CALL( mockContext, getEntity( 0 ) )
    .WillOnce( testing::Return( &unit ) );
    
    EXPECT_CALL( mockContext, getEntity( position ) )
    .WillOnce( testing::Return( &entity ) );
    
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

TEST_F( ActionsProviderTest, getTileOpponentEntityAndStructure ) {
    Point position( 0, 2 );
    
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

TEST_F( ActionsProviderTest, getTileOwnEntityAndStructure ) {
    Point position( 0, 2 );
    
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
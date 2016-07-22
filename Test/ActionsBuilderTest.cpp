//
//  ActionsBuilderTest.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 13/07/16.
//  Copyright (c) 2016 Alvaro Chambi Campos. All rights reserved.
//

#include <iostream>
#include "ActionsBuilder.h"
#include "MockMap.h"
#include "gtest/gtest.h"

class ActionsBuilderTest : public ::testing::Test {
public:
    virtual void SetUp() {
    }
    
    virtual void TearDown() {
    }
    
    MockMap mockContext;
    ActionsBuilder actionsBuilder;
};

TEST_F( ActionsBuilderTest, appendAttackNoAvailable ) {
    Point position( 1, 1 );
    Unit unit;
    unit.setid( 0 );
    unit.setMovement( 1 );
    unit.setAttackRange( 1 );
    unit.setPosition( 3, 0 );
    
    Unit entity;
    
    std::vector<Action*> vector;
    
    EXPECT_CALL( mockContext, getNumColumns() )
    .WillOnce( testing::Return( 3 ) );
    EXPECT_CALL( mockContext, getNumRows() )
    .WillOnce( testing::Return( 3 ) );
    
    EXPECT_CALL( mockContext, getEntity( 0 ) )
    .WillOnce( testing::Return( &unit ) );
    
    EXPECT_CALL( mockContext, getEntity( position ) )
    .Times( 2 )
    .WillRepeatedly( testing::Return( &entity ) );
    
    EXPECT_CALL( mockContext, getEntity( Point( 0, 0 ) ) )
    .WillOnce( testing::Return( nullptr ) );
    EXPECT_CALL( mockContext, getEntity( Point( 1, 0 ) ) )
    .WillOnce( testing::Return( nullptr ) );
    EXPECT_CALL( mockContext, getEntity( Point( 2, 0 ) ) )
    .WillOnce( testing::Return( nullptr ) );
    EXPECT_CALL( mockContext, getEntity( Point( 0, 1 ) ) )
    .WillOnce( testing::Return( nullptr ) );
    EXPECT_CALL( mockContext, getEntity( Point( 2, 1 ) ) )
    .WillOnce( testing::Return( nullptr ) );
    EXPECT_CALL( mockContext, getEntity( Point( 0, 2 ) ) )
    .WillOnce( testing::Return( nullptr ) );
    EXPECT_CALL( mockContext, getEntity( Point( 1, 2 ) ) )
    .WillOnce( testing::Return( nullptr ) );
    EXPECT_CALL( mockContext, getEntity( Point( 2, 2 ) ) )
    .WillOnce( testing::Return( nullptr ) );
    
    actionsBuilder.createAppendAttackActions( mockContext, 0, position,
                                              vector);

    ASSERT_TRUE( vector.empty() );
}

TEST_F( ActionsBuilderTest, appendAttackAvailable ) {
    Point position( 1, 1 );
    
    Unit unit;
    unit.setid( 0 );
    unit.setMovement( 1 );
    unit.setAttackRange( 1 );
    unit.setPosition( 0, 2 );
    
    Unit entity;
    entity.setPosition( 1, 1 );
    
    std::vector<Action*> vector;
    
    EXPECT_CALL( mockContext, getNumColumns() )
    .WillOnce( testing::Return( 3 ) );
    EXPECT_CALL( mockContext, getNumRows() )
    .WillOnce( testing::Return( 3 ) );
    
    EXPECT_CALL( mockContext, getEntity( 0 ) )
    .WillOnce( testing::Return( &unit ) );
    
    EXPECT_CALL( mockContext, getEntity( position ) )
    .Times( 2 )
    .WillRepeatedly( testing::Return( &entity ) );
    
    EXPECT_CALL( mockContext, getEntity( Point( 0, 0 ) ) )
    .WillOnce( testing::Return( nullptr ) );
    EXPECT_CALL( mockContext, getEntity( Point( 1, 0 ) ) )
    .WillOnce( testing::Return( nullptr ) );
    EXPECT_CALL( mockContext, getEntity( Point( 2, 0 ) ) )
    .WillOnce( testing::Return( nullptr ) );
    EXPECT_CALL( mockContext, getEntity( Point( 0, 1 ) ) )
    .WillOnce( testing::Return( nullptr ) );
    EXPECT_CALL( mockContext, getEntity( Point( 2, 1 ) ) )
    .WillOnce( testing::Return( nullptr ) );
    EXPECT_CALL( mockContext, getEntity( Point( 0, 2 ) ) )
    .WillOnce( testing::Return( nullptr ) );
    EXPECT_CALL( mockContext, getEntity( Point( 1, 2 ) ) )
    .WillOnce( testing::Return( nullptr ) );
    EXPECT_CALL( mockContext, getEntity( Point( 2, 2 ) ) )
    .WillOnce( testing::Return( nullptr ) );
    
    actionsBuilder.createAppendAttackActions( mockContext, 0, position,
                                             vector);
    
    ASSERT_EQ( 2, vector.size() );
}

TEST_F( ActionsBuilderTest, appendAttackAllPositionsAvailable ) {
    Point position( 1, 1 );
    Unit unit;
    unit.setid( 0 );
    unit.setMovement( 3 );
    unit.setAttackRange( 1 );
    unit.setPosition( 0, 2 );
    
    Unit entity;
    entity.setPosition( 1, 1 );
    
    std::vector<Action*> vector;
    
    EXPECT_CALL( mockContext, getNumColumns() )
    .WillOnce( testing::Return( 3 ) );
    EXPECT_CALL( mockContext, getNumRows() )
    .WillOnce( testing::Return( 3 ) );
    
    EXPECT_CALL( mockContext, getEntity( 0 ) )
    .WillOnce( testing::Return( &unit ) );
    
    EXPECT_CALL( mockContext, getEntity( position ) )
    .Times( 2 )
    .WillRepeatedly( testing::Return( &entity ) );
    
    EXPECT_CALL( mockContext, getEntity( Point( 0, 0 ) ) )
    .WillOnce( testing::Return( nullptr ) );
    EXPECT_CALL( mockContext, getEntity( Point( 1, 0 ) ) )
    .WillOnce( testing::Return( nullptr ) );
    EXPECT_CALL( mockContext, getEntity( Point( 2, 0 ) ) )
    .WillOnce( testing::Return( nullptr ) );
    EXPECT_CALL( mockContext, getEntity( Point( 0, 1 ) ) )
    .WillOnce( testing::Return( nullptr ) );
    EXPECT_CALL( mockContext, getEntity( Point( 2, 1 ) ) )
    .WillOnce( testing::Return( nullptr ) );
    EXPECT_CALL( mockContext, getEntity( Point( 0, 2 ) ) )
    .WillOnce( testing::Return( nullptr ) );
    EXPECT_CALL( mockContext, getEntity( Point( 1, 2 ) ) )
    .WillOnce( testing::Return( nullptr ) );
    EXPECT_CALL( mockContext, getEntity( Point( 2, 2 ) ) )
    .WillOnce( testing::Return( nullptr ) );
    
    actionsBuilder.createAppendAttackActions( mockContext, 0, position,
                                              vector);
    
    ASSERT_EQ( 4, vector.size() );
}

TEST_F( ActionsBuilderTest, appendAttackUnitAndEntitySamePosition ) {
    Point position( 1, 1 );
    Unit unit;
    unit.setid( 0 );
    unit.setMovement( 1 );
    unit.setAttackRange( 1 );
    unit.setPosition( 1, 1 );
    
    Unit entity;
    entity.setPosition( 1, 1 );
    
    std::vector<Action*> vector;
    
    EXPECT_CALL( mockContext, getEntity( 0 ) )
    .WillOnce( testing::Return( &unit ) );
    
    EXPECT_CALL( mockContext, getEntity( position ) )
    .WillOnce( testing::Return( &entity ) );
    
    ASSERT_ANY_THROW(
            actionsBuilder.createAppendAttackActions( mockContext, 0,
                                                     position, vector); );
}
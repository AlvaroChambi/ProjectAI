//
//  MovementTest.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 27/07/16.
//  Copyright (c) 2016 Alvaro Chambi Campos. All rights reserved.
//

#include <iostream>
#include "Movement.h"
#include "gtest/gtest.h"
#include "MockMap.h"
#include "MoveCommand.h"

class MovementTest : public ::testing::Test {
public:
    MovementTest() {
        
    }
    
    virtual void SetUp() {

    }
    
    virtual void TearDown() {
    }
};

TEST_F( MovementTest, addActionFirstValueTest ) {
    Movement movement;
    
    Action action0;
    
    ASSERT_TRUE( movement.addAction( action0 ) );
    ASSERT_EQ( 1, movement.getActions().size() );
}

TEST_F( MovementTest, addActionNewValueTest ) {
    Movement movement;
    
    Action action0;
    Action action1;
    
    movement.addAction( action0 );
    
    ASSERT_TRUE( movement.addAction( action1 ) );
    ASSERT_EQ( 2, movement.getActions().size() );
}

TEST_F( MovementTest, addActionRepeatedValueTest ) {
    Movement movement;
    MockMap mockMap;
    
    Action action0;
    MoveCommand moveCommand0( mockMap, 0, Point( 0, 0 ) );
    action0.moveCommand = &moveCommand0;
    Action action1;
    MoveCommand moveCommand1( mockMap, 0, Point( 0, 0 ) );
    action1.moveCommand = &moveCommand1;
    
    movement.addAction( action0 );
    
    ASSERT_FALSE( movement.addAction( action1 ) );
    ASSERT_EQ( 1, movement.getActions().size() );
}
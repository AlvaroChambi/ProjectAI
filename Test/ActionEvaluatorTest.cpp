//
//  ActionEvaluatorTest.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 01/08/16.
//  Copyright (c) 2016 Alvaro Chambi Campos. All rights reserved.
//

#include "ActionEvaluator.h"
#include "MockMap.h"
#include "gtest/gtest.h"

#include <vector>

class ActionEvaluatorTest : public ::testing::Test {
public:
    ActionEvaluatorTest() {
        
    }
    
    virtual void SetUp() {

    }
    
    virtual void TearDown() {
        
    }
    
    ActionEvaluator evaluator;
    MockMap context;
};

TEST_F( ActionEvaluatorTest, AlliesInfluenceTest ) {
    Unit* unit0 = new Unit;
    Unit* unit1 = new Unit;
    unit0->setid( 0 );
    unit0->setPosition( 1, 1 );
    unit1->setid( 1 );
    unit1->setPosition( 1, 2 );
    
    Player player;
    player.addUnit( *unit0 );
    player.addUnit( *unit1 );
    player.setMap( &context );
    EXPECT_CALL( context, getEntity( 0 ) ).WillOnce(
                                        testing::Return( unit0 ) );
    EXPECT_CALL( context, getEntity( 1 ) ).WillOnce(
                                        testing::Return( unit1 ) );
    
    EXPECT_CALL( context, getPlayer() ).WillOnce( testing::ReturnRef( player ) );
    
    ASSERT_FLOAT_EQ( 2.5, evaluator.getAlliesInfluence(  Point( 0, 0 ),
                                                         context ) );
}

TEST_F( ActionEvaluatorTest, OpponentsInfluenceTest ) {
    
    Unit* unit0 = new Unit;
    Unit* unit1 = new Unit;
    unit0->setid( 0 );
    unit0->setPosition( 1, 1 );
    unit1->setid( 1 );
    unit1->setPosition( 1, 2 );
    
    Player player;
    player.addUnit( *unit0 );
    player.addUnit( *unit1 );
    player.setMap( &context );
    

    EXPECT_CALL( context, getEntity( 0 ) ).WillOnce(
                                        testing::Return( unit0 ) );
    EXPECT_CALL( context, getEntity( 1 ) ).WillOnce(
                                        testing::Return( unit1 ) );
    
    EXPECT_CALL( context, getOpponent() ).WillOnce(
                                                testing::ReturnRef( player ) );
    
    ASSERT_FLOAT_EQ( 2.5, evaluator.getOpponentsInfluence(  Point( 0, 0 ),
                                                            context ) );
}

TEST_F( ActionEvaluatorTest, EvaluateValuesTest ) {
    float headquarterInfluence = 5;
    float opponentHeadquarterInfluence = 10;
    float alliesInfluence = 2.5;
    float opponentsInfluence = 5;
    
    ASSERT_FLOAT_EQ( 0.5, evaluator.evaluateValues( headquarterInfluence,
                                            opponentHeadquarterInfluence,
                                            alliesInfluence,
                                            opponentsInfluence ) );
}

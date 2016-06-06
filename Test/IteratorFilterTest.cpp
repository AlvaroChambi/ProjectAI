//
//  AreaFilterTest.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 2/6/16.
//  Copyright © 2016 Alvaro Chambi Campos. All rights reserved.
//

#include "UnitFilter.h"
#include "AreaIterator.h"
#include "gtest/gtest.h"
#include "MockMap.h"

class IteratorFilterTest : public ::testing::Test {
public:
    IteratorFilterTest() {
        
    }
    
    virtual void SetUp() {
        areaIterator = new AreaIterator;
    }
    
    virtual void TearDown() {
    }
    
    AreaIterator* areaIterator;
    IteratorFilter* iteratorFiter;
    MockMap map;
};

TEST_F( IteratorFilterTest, hasNextAvailablePosition ) {
    Unit* unit = new Unit;
    unit->setPosition( 1, 1 );
    unit->setMovement( 1 );
    
    EXPECT_CALL( map , isValidPosition( testing::_ ) )
    .Times( 2 )
    .WillRepeatedly( testing::Return( true ) );
    
    std::pair<Point, Point>* area = new std::pair<Point,Point>;
    area->first = Point( 0, 0 );
    area->second = Point( 2, 2 );
    
    areaIterator->setArea( area );
    iteratorFiter = new UnitMovementFilter( areaIterator, &map, unit );
    
    ASSERT_TRUE( iteratorFiter->hasNext() );
    Point position = iteratorFiter->next();
    
    ASSERT_EQ( 1 , position.x );
    ASSERT_EQ( 0 , position.y );
}

TEST_F( IteratorFilterTest, notNextAvailablePosition ) {
    Unit* unit = new Unit;
    unit->setPosition( 1, 1 );
    unit->setMovement( 1 );
    
    std::pair<Point, Point>* area = new std::pair<Point,Point>;
    area->first = Point( 0, 0 );
    area->second = Point( 2, 2 );
    
    areaIterator->setArea( area );
    iteratorFiter = new UnitMovementFilter( areaIterator, &map, unit );
    
    ASSERT_FALSE( iteratorFiter->hasNext() );
}

TEST_F( IteratorFilterTest, IllegalNextCall ) {
    Unit* unit = new Unit;
    iteratorFiter = new UnitMovementFilter( areaIterator, &map, unit );
    ASSERT_ANY_THROW( iteratorFiter->next() );
}

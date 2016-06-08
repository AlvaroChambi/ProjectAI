//
//  UnitMovementFilterTest.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 8/6/16.
//  Copyright © 2016 Alvaro Chambi Campos. All rights reserved.
//

#include "gtest/gtest.h"

#include "UnitFilter.h"
#include "MockIterator.h"
#include "MockMap.h"

class UnitMovementFilterTest : public ::testing::Test {
public:
    UnitMovementFilterTest() {
        
    }
    
    virtual void SetUp() {

    }
    
    virtual void TearDown() {
        
    }
    
    UnitMovementFilter* movementFilter;
    MockIterator iterator;
    MockMap map;
};

TEST_F( UnitMovementFilterTest, IsInvalidatedEmptyInvalidatedList ) {
    Unit* unit = new Unit;
    movementFilter = new UnitMovementFilter( &iterator, &map, unit );
    
    ASSERT_FALSE( movementFilter->isInvalidated( Point( 0, 0 ) ) );
    ASSERT_EQ( 1, movementFilter->getInvalidatedPositions().size() );
}

TEST_F( UnitMovementFilterTest, IsInvalidatedItemInList ) {
    Unit* unit = new Unit;
    movementFilter = new UnitMovementFilter( &iterator, &map, unit );
    std::vector<Point> invalidated;
    invalidated.push_back( Point( 1, 1 ) );
    movementFilter->setInvalidatedPositions( invalidated );
    
    ASSERT_TRUE( movementFilter->isInvalidated( Point( 1, 1 ) ) );
    ASSERT_EQ( 1, movementFilter->getInvalidatedPositions().size() );
}

TEST_F( UnitMovementFilterTest, IsInvalidatedNewItem ) {
    Unit* unit = new Unit;
    movementFilter = new UnitMovementFilter( &iterator, &map, unit );
    std::vector<Point> invalidated;
    invalidated.push_back( Point( 1, 1 ) );
    movementFilter->setInvalidatedPositions( invalidated );
    
    ASSERT_FALSE( movementFilter->isInvalidated( Point( 2, 2 ) ) );
    ASSERT_EQ( 2, movementFilter->getInvalidatedPositions().size() );
}

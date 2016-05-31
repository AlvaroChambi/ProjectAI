//
//  MapTest.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 31/5/16.
//  Copyright © 2016 Alvaro Chambi Campos. All rights reserved.
//

#include <iostream>
#include "Map.h"
#include "gtest/gtest.h"

class MapTest : public ::testing::Test {
public:
    MapTest() {
        map = new Map;
    }
    
    virtual void SetUp() {

    }
    
    virtual void TearDown() {
    }
    
    Map* map;
};

TEST_F( MapTest, getBoundingAreaCenterTest ) {
    Point origin = Point( 7, 5 );
    int range = 2;
    
    std::pair<Point,Point>* result;
    result = map->getBoundingArea( origin, range );
    
    ASSERT_EQ( Point( 5, 3 ) , result->first );
    ASSERT_EQ( Point( 9, 7 ) , result->second );
}

TEST_F( MapTest, getBoundingAreaCroppedTopTest ) {
    Point origin = Point( 7, 0 );
    int range = 2;
    
    std::pair<Point,Point>* result;
    result = map->getBoundingArea( origin, range );
    
    ASSERT_EQ( Point( 5, 0 ) , result->first );
    ASSERT_EQ( Point( 9, 2 ) , result->second );
}

TEST_F( MapTest, getBoundingAreaCroppedBottomTest ) {
    Point origin = Point( 7, 9 );
    int range = 2;
    
    std::pair<Point,Point>* result;
    result = map->getBoundingArea( origin, range );
    
    ASSERT_EQ( Point( 5, 7 ) , result->first );
    ASSERT_EQ( Point( 9, 9 ) , result->second );
}

TEST_F( MapTest, getBoundingAreaCroppedLeftTest ) {
    Point origin = Point( 0, 5 );
    int range = 2;
    
    std::pair<Point,Point>* result;
    result = map->getBoundingArea( origin, range );
    
    ASSERT_EQ( Point( 0, 3 ) , result->first );
    ASSERT_EQ( Point( 2, 7 ) , result->second );
}

TEST_F( MapTest, getBoundingAreaCroppedRightTest ) {
    Point origin = Point( 14, 5 );
    int range = 2;
    
    std::pair<Point,Point>* result;
    result = map->getBoundingArea( origin, range );
    
    ASSERT_EQ( Point( 12, 3 ) , result->first );
    ASSERT_EQ( Point( 14, 7 ) , result->second );
}

TEST_F( MapTest, getBoundingAreaCroppedTopLeftTest ) {
    Point origin = Point( 0, 0 );
    int range = 2;
    
    std::pair<Point,Point>* result;
    result = map->getBoundingArea( origin, range );
    
    ASSERT_EQ( Point( 0, 0 ) , result->first );
    ASSERT_EQ( Point( 2, 2 ) , result->second );
}

TEST_F( MapTest, getBoundingAreaCroppedTopRightTest ) {
    Point origin = Point( 14, 0 );
    int range = 2;
    
    std::pair<Point,Point>* result;
    result = map->getBoundingArea( origin, range );
    
    ASSERT_EQ( Point( 12, 0 ) , result->first );
    ASSERT_EQ( Point( 14, 2 ) , result->second );
}

TEST_F( MapTest, getBoundingAreaCroppedBottomLeftTest ) {
    Point origin = Point( 0, 9 );
    int range = 2;
    
    std::pair<Point,Point>* result;
    result = map->getBoundingArea( origin, range );
    
    ASSERT_EQ( Point( 0, 7 ) , result->first );
    ASSERT_EQ( Point( 2, 9 ) , result->second );
}

TEST_F( MapTest, getBoundingAreaCroppedBottomRightTest ) {
    Point origin = Point( 14, 9 );
    int range = 2;
    
    std::pair<Point,Point>* result;
    result = map->getBoundingArea( origin, range );
    
    ASSERT_EQ( Point( 12, 7 ) , result->first );
    ASSERT_EQ( Point( 14, 9 ) , result->second );
}

TEST_F( MapTest, getBoundingAreaCeroRange ) {
    Point origin = Point( 0, 9 );
    int range = 0;
    
    ASSERT_ANY_THROW( map->getBoundingArea( origin , range ) );
}

TEST_F( MapTest, getBoundingAreaNegativeRange ) {
    Point origin = Point( 0, 9 );
    int range = -10;
    
    ASSERT_ANY_THROW( map->getBoundingArea( origin , range ) );
}

TEST_F( MapTest, getBoundingAreaInvalidPosition ) {
    Point origin = Point( 0, 20 );
    int range = 2;
    
    ASSERT_ANY_THROW( map->getBoundingArea( origin , range ) );
}
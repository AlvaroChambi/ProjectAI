//
//  PointTest.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 31/5/16.
//  Copyright © 2016 Alvaro Chambi Campos. All rights reserved.
//

#include <iostream>
#include "Point.h"
#include "gtest/gtest.h"

class PointTest : public ::testing::Test {
public:
    PointTest() {
        point = new Point( 0, 0 );
    }
    
    virtual void SetUp() {

    }
    
    virtual void TearDown() {
    }
    
    Point* point;
};

TEST_F( PointTest, PointGetDistanceTestPositive ) {
    
    Point destination = Point( 1 , 1 );
    int distance = point->distance( destination );
    ASSERT_EQ( 2 , distance );
}

TEST_F( PointTest, PointGetDistanceTestXNegative ) {
    
    Point destination = Point( -1 , 1 );
    int distance = point->distance( destination );
    ASSERT_EQ( 2 , distance );
}

TEST_F( PointTest, PointGetDistanceTestYNegative ) {
    
    Point destination = Point( 1 , -1 );
    int distance = point->distance( destination );
    ASSERT_EQ( 2 , distance );
}

TEST_F( PointTest, PointGetDistanceTestNegative ) {
    
    Point destination = Point( -1 , -1 );
    int distance = point->distance( destination );
    ASSERT_EQ( 2 , distance );
}

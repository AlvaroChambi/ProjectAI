//
//  AreaIteratorTest.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 2/6/16.
//  Copyright © 2016 Alvaro Chambi Campos. All rights reserved.
//

#include "AreaIterator.h"
#include "gtest/gtest.h"

class AreaIteratorTest : public ::testing::Test {
public:
    AreaIteratorTest() {
        areaIterator = new AreaIterator;
    }
    
    virtual void SetUp() {

    }
    
    virtual void TearDown() {
    }
    
    AreaIterator* areaIterator;
};

TEST_F( AreaIteratorTest, buildAreaCenterTest ) {
    Point origin = Point( 7, 5 );
    int range = 2;
    
    areaIterator->buildArea( origin, range, 15, 10 );
    std::pair<Point,Point>* result = areaIterator->getArea();
    
    ASSERT_EQ( 5, result->first.x );
    ASSERT_EQ( 3, result->first.y );
    
    ASSERT_EQ( 9, result->second.x );
    ASSERT_EQ( 7, result->second.y );
    
}

TEST_F( AreaIteratorTest, buildAreaCroppedTopTest ) {
    Point origin = Point( 7, 0 );
    int range = 2;
    
    areaIterator->buildArea( origin, range, 15, 10 );
    std::pair<Point,Point>* result = areaIterator->getArea();
    
    ASSERT_EQ( 5, result->first.x );
    ASSERT_EQ( 0, result->first.y );
    
    ASSERT_EQ( 9, result->second.x );
    ASSERT_EQ( 2, result->second.y );
}

TEST_F( AreaIteratorTest, buildAreaCroppedBottomTest ) {
    Point origin = Point( 7, 9 );
    int range = 2;
    
    areaIterator->buildArea( origin, range, 15, 10 );
    std::pair<Point,Point>* result = areaIterator->getArea();
    
    ASSERT_EQ( 5, result->first.x );
    ASSERT_EQ( 7, result->first.y );
    
    ASSERT_EQ( 9, result->second.x );
    ASSERT_EQ( 9, result->second.y );
}

TEST_F( AreaIteratorTest, buildAreaCroppedLeftTest ) {
    Point origin = Point( 0, 5 );
    int range = 2;
    
    areaIterator->buildArea( origin, range, 15, 10 );
    std::pair<Point,Point>* result = areaIterator->getArea();
    
    ASSERT_EQ( 0, result->first.x );
    ASSERT_EQ( 3, result->first.y );
    
    ASSERT_EQ( 2, result->second.x );
    ASSERT_EQ( 7, result->second.y );
}

TEST_F( AreaIteratorTest, buildAreaCroppedRightTest ) {
    Point origin = Point( 14, 5 );
    int range = 2;
    
    areaIterator->buildArea( origin, range, 15, 10 );
    std::pair<Point,Point>* result = areaIterator->getArea();
    
    ASSERT_EQ( 12, result->first.x );
    ASSERT_EQ( 3, result->first.y );
    
    ASSERT_EQ( 14, result->second.x );
    ASSERT_EQ( 7, result->second.y );
}

TEST_F( AreaIteratorTest, buildAreaCroppedTopLeftTest ) {
    Point origin = Point( 0, 0 );
    int range = 2;
    
    areaIterator->buildArea( origin, range, 15, 10 );
    std::pair<Point,Point>* result = areaIterator->getArea();
    
    ASSERT_EQ( 0, result->first.x );
    ASSERT_EQ( 0, result->first.y );
    
    ASSERT_EQ( 2, result->second.x );
    ASSERT_EQ( 2, result->second.y );
}

TEST_F( AreaIteratorTest, buildAreaCroppedTopRightTest ) {
    Point origin = Point( 14, 0 );
    int range = 2;
    
    areaIterator->buildArea( origin, range, 15, 10 );
    std::pair<Point,Point>* result = areaIterator->getArea();
    
    ASSERT_EQ( 12, result->first.x );
    ASSERT_EQ( 0, result->first.y );
    
    ASSERT_EQ( 14, result->second.x );
    ASSERT_EQ( 2, result->second.y );
}

TEST_F( AreaIteratorTest, buildAreaCroppedBottomLeftTest ) {
    Point origin = Point( 0, 9 );
    int range = 2;
    
    areaIterator->buildArea( origin, range, 15, 10 );
    std::pair<Point,Point>* result = areaIterator->getArea();
    
    ASSERT_EQ( 0, result->first.x );
    ASSERT_EQ( 7, result->first.y );
    
    ASSERT_EQ( 2, result->second.x );
    ASSERT_EQ( 9, result->second.y );
}

TEST_F( AreaIteratorTest, buildAreaCroppedBottomRightTest ) {
    Point origin = Point( 14, 9 );
    int range = 2;
    
    areaIterator->buildArea( origin, range, 15, 10 );
    std::pair<Point,Point>* result = areaIterator->getArea();
    
    ASSERT_EQ( 12, result->first.x );
    ASSERT_EQ( 7, result->first.y );
    
    ASSERT_EQ( 14, result->second.x );
    ASSERT_EQ( 9, result->second.y );
}

TEST_F( AreaIteratorTest, buildAreaCeroRange ) {
    Point origin = Point( 0, 9 );
    int range = 0;
    
    ASSERT_ANY_THROW( areaIterator->buildArea( origin, range, 15, 10 ) );
}

TEST_F( AreaIteratorTest, buildAreaNegativeRange ) {
    Point origin = Point( 0, 9 );
    int range = -10;
    
    ASSERT_ANY_THROW( areaIterator->buildArea( origin, range, 15, 10 ) );
}

TEST_F( AreaIteratorTest, buildAreaInvalidPosition ) {
    Point origin = Point( 0, 20 );
    int range = 2;
    
    ASSERT_ANY_THROW( areaIterator->buildArea( origin, range, 15, 10 ) );
}

TEST_F( AreaIteratorTest, nextPostionSameRowIncrement ) {
    std::pair<Point,Point>* area = new std::pair<Point, Point>;
    area->first = Point( 0, 0 );
    area->second = Point( 1, 1 );
    areaIterator->setArea( area );
    areaIterator->setCurrentPosition( 1 );
    
    Point* position = areaIterator->nextPosition();
    
    ASSERT_EQ( 2 , areaIterator->getCurrentPosition() );
    ASSERT_EQ( 1 , position->x );
    ASSERT_EQ( 0, position->y );
}

TEST_F( AreaIteratorTest, nextPostionNextRowIncrement ) {
    std::pair<Point,Point>* area = new std::pair<Point, Point>;
    area->first = Point( 0, 0 );
    area->second = Point( 1, 1 );
    areaIterator->setArea( area );
    areaIterator->setCurrentPosition( 2 );
    
    Point* position = areaIterator->nextPosition();
    
    ASSERT_EQ( 3 , areaIterator->getCurrentPosition() );
    ASSERT_EQ( 0 , position->x );
    ASSERT_EQ( 1, position->y );
}

TEST_F( AreaIteratorTest, nextPostionAreaWithOffset ) {
    std::pair<Point,Point>* area = new std::pair<Point, Point>;
    area->first = Point( 5, 5 );
    area->second = Point( 6, 6 );
    areaIterator->setArea( area );
    areaIterator->setCurrentPosition( 1 );
    
    Point* position = areaIterator->nextPosition();
    
    ASSERT_EQ( 2 , areaIterator->getCurrentPosition() );
    ASSERT_EQ( 6 , position->x );
    ASSERT_EQ( 5, position->y );
}

TEST_F( AreaIteratorTest, nextPostionAreaOffsetRowIncrement ) {
    std::pair<Point,Point>* area = new std::pair<Point, Point>;
    area->first = Point( 5, 5 );
    area->second = Point( 6, 6 );
    areaIterator->setArea( area );
    areaIterator->setCurrentPosition( 2 );
    
    Point* position = areaIterator->nextPosition();
    
    ASSERT_EQ( 3 , areaIterator->getCurrentPosition() );
    ASSERT_EQ( 5 , position->x );
    ASSERT_EQ( 6, position->y );
}

TEST_F( AreaIteratorTest, nextPostionFinishReached ) {
    std::pair<Point,Point>* area = new std::pair<Point, Point>;
    area->first = Point( 0, 0 );
    area->second = Point( 1, 1 );
    areaIterator->setArea( area );
    areaIterator->setCurrentPosition( 4 );
    
    EXPECT_EQ( nullptr, areaIterator->nextPosition() );
}

TEST_F( AreaIteratorTest, nextPostionAreaNotDefined ) {
    ASSERT_ANY_THROW( areaIterator->nextPosition(); );
}

TEST_F( AreaIteratorTest, nextPostionIllegalArea ) {
    std::pair<Point,Point>* area = new std::pair<Point, Point>;
    area->first = Point( 0, 0 );
    area->second = Point( -1, 1 );
    areaIterator->setArea( area );
    ASSERT_ANY_THROW( areaIterator->nextPosition(); );
}
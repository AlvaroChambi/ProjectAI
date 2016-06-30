//
//  MapLayerTest.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 30/06/16.
//  Copyright (c) 2016 Alvaro Chambi Campos. All rights reserved.
//

#include "MapLayer.h"
#include "gtest/gtest.h"

class MapLayerTest : public ::testing::Test {
public:
    MapLayerTest() {
        
    }
    
    virtual void SetUp() {

    }
    
    virtual void TearDown() {
    }
    
    MapLayer<int*> mapLayer;
};

TEST_F( MapLayerTest,MapLayerResizeTest ) {
    mapLayer.resize( 2, 2 );
    
    ASSERT_EQ( 4, mapLayer.size() );
    
    ASSERT_EQ( nullptr, mapLayer.at( 0 ) );
    ASSERT_EQ( nullptr, mapLayer.at( 1 ) );
    ASSERT_EQ( nullptr, mapLayer.at( 2 ) );
    ASSERT_EQ( nullptr, mapLayer.at( 3 ) );
}

TEST_F( MapLayerTest,MapLayerResizeTestInvalidValues ) {
    ASSERT_ANY_THROW( mapLayer.resize( 0, -1 ); );
}

TEST_F( MapLayerTest, MapLayerSetValidValue ) {
    mapLayer.resize( 2, 2 );
    
    int value = 2;
    
    mapLayer.set( &value, Point( 0, 1 ) );
    
    ASSERT_EQ( 4, mapLayer.size() );
    
    ASSERT_EQ( nullptr, mapLayer.at( 0 ) );
    ASSERT_EQ( nullptr, mapLayer.at( 1 ) );
    ASSERT_EQ( value, *mapLayer.at( 2 ) );
    ASSERT_EQ( nullptr, mapLayer.at( 3 ) );
}
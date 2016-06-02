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
//
//  UnitTest.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 1/6/16.
//  Copyright © 2016 Alvaro Chambi Campos. All rights reserved.
//

#include "Unit.h"
#include "gtest/gtest.h"
#include "MockMap.h"
#include "Player.h"

class UnitTest : public ::testing::Test {
public:
    UnitTest() {
    }
    
    virtual void SetUp() {
        unit = new Unit;
    }
    
    virtual void TearDown() {
    }
    
    Unit* unit;
    MockMap map;
};

//TODO: Reimplement tests, functionality added and not tested
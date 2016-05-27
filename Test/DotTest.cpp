//
//  DotTest.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 27/05/16.
//  Copyright (c) 2016 Alvaro Chambi Campos. All rights reserved.
//

#include <iostream>
#include "DotPath.h"
#include "gtest/gtest.h"

class DotTest : public ::testing::Test {
public:
    DotTest() {
        
    }
    
    virtual void SetUp() {
        path.clear();
        dotPath = new DotPath;
    }
    
    virtual void TearDown() {
    }
    
    DotPath* dotPath;
    std::vector<std::string> path;
};

TEST_F( DotTest, DotTestBuildDotPath ) {
    
    dotPath->addNode( "0" );
    dotPath->addNode( "1" );
    dotPath->addNode( "2" );
    
    ASSERT_EQ( "0--1--2", dotPath->getLine() );
}


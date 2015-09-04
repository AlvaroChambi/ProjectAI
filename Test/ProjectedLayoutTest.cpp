//
//  ProjectedLayoutTest.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 3/9/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#include <stdio.h>

#include "gtest/gtest.h"
#include "ProjectedLayout.h"

class ProjectedLayoutTest : public ::testing::Test
{
public:
    
    ProjectedLayoutTest()
    {
        layout = new ProjectedLayout;
    }
    
    virtual void SetUp()
    {
        layout->width = 640;
        layout->height = 480;
    }
    
    virtual void TearDown()
    {

    }
    
    ProjectedLayout* layout;
    
};

TEST_F(ProjectedLayoutTest, ProjectedLayoutsDispositionTest)
{
    std::vector<Point> dispositionPoints = layout->projectedLayoutsDisposition();
    Point start = dispositionPoints.at(0);
    Point end = dispositionPoints.at(1);
    ASSERT_EQ(0, start.x);
    ASSERT_EQ(120, start.y);
    
    ASSERT_EQ(640, end.x);
    ASSERT_EQ(360, end.y);
    
    start = dispositionPoints.at(2);
    end = dispositionPoints.at(3);
    ASSERT_EQ(80, start.x);
    ASSERT_EQ(90, start.y);
    
    ASSERT_EQ(560, end.x);
    ASSERT_EQ(270, end.y);
    
    start = dispositionPoints.at(4);
    end = dispositionPoints.at(5);
    ASSERT_EQ(160, start.x);
    ASSERT_EQ(60, start.y);
    
    ASSERT_EQ(480, end.x);
    ASSERT_EQ(180, end.y);
}

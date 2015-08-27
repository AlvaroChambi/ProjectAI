//
//  main.cpp
//  Test
//
//  Created by Alvaro Chambi Campos on 4/6/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#include <iostream>
#include "UIComponent.h"
#include "Layout.h"
#include "gtest/gtest.h"

int main(int argc, char ** argv) {
    //::txesting::InitGoogleTest(&argc, argv);
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


TEST(UIComponentPositionUpdate,CenterComponentInParent)
{
    UIComponent* component = new UIComponent(-1);
    component->width = 100;
    component->height = 100;
    
    component->center(Point(0,0), 500, 500);
    
    ASSERT_EQ(200, component->position.x);
    ASSERT_EQ(200, component->position.y);
}

TEST(UIComponentPositionUpdate, UpComponentInParent)
{
    UIComponent* component = new Layout;
    component->width = 100;
    component->height = 100;
    
    component->up(Point(0,0), 500, 500);
    
    ASSERT_EQ(0, component->position.x);
    ASSERT_EQ(0, component->position.y);
}

TEST(UIComponentPositionUpdate, DownComponentInParent)
{
    UIComponent* component = new Layout;
    component->width = 100;
    component->height = 100;
    
    component->down(Point(0,0), 500, 500);
    
    ASSERT_EQ(0, component->position.x);
    ASSERT_EQ(400, component->position.y);
}

TEST(UIComponentPositionUpdate, CenterDownComponentInParent)
{
    UIComponent* component = new Layout;
    component->width = 100;
    component->height = 100;
    
    component->centerDown(Point(0,0), 500, 500);
    
    ASSERT_EQ(200, component->position.x);
    ASSERT_EQ(400, component->position.y);
}

//
//  LayoutTest.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 29/8/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#include <stdio.h>
#include "gtest/gtest.h"
#include "VerticalLayout.h"
#include "HorizontalLayout.h"

class LayoutTest : public ::testing::Test
{
public:
    
    LayoutTest()
    {
        verticalLayout = new VerticalLayout;
        horizontalLayout = new HorizontalLayout;
        component0 = new UIComponent;
        component1 = new UIComponent;
        component2 = new UIComponent;
    }
    
    virtual void SetUp()
    {
        Params params = Params(100, 100, CENTER);
        verticalLayout->width = 500;
        verticalLayout->height = 1500;
        
        horizontalLayout->width = 1500;
        horizontalLayout->height = 500;
        
        component0->setParams(params);
        component1->setParams(params);
        component2->setParams(params);
    }
    
    virtual void TearDown()
    {
        verticalLayout->cleanComponents();
    }
    
    VerticalLayout* verticalLayout;
    HorizontalLayout* horizontalLayout;
    UIComponent* component0;
    UIComponent* component1;
    UIComponent* component2;
};
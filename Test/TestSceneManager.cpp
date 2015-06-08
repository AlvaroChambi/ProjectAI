//
//  TestSceneManager.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 4/6/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#include "gtest/gtest.h"
#include "SceneManager.h"
#include "MockScene.h"

//Test setActual scene

//Test getScene

class TestSceneManager : public testing::Test
{
protected:
    SceneManager manager;
    
    MockScene* scene1 = new MockScene;
    MockScene* scene2 = new MockScene;
    MockScene* scene3 = new MockScene;
    
    virtual void SetUp()
    {
        manager.registerScene(scene1, "scene1");
        manager.registerScene(scene2, "scene2");
        manager.registerScene(scene3, "scene3");
    }
};

TEST_F(TestSceneManager, getScene)
{
    Scene* saved1 = manager.getScene("scene1");
    EXPECT_TRUE(saved1 == scene1);
}
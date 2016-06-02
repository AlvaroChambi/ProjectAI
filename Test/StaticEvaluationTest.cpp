//
//  StaticEvaluationTest.cpp
//  ProjectWar
//
//  Created by Pablo Luis Gutierrez on 02/06/16.
//  Copyright © 2016 Alvaro Chambi Campos. All rights reserved.
//

#include <stdio.h>
#include "GameState.h"
#include "Player.h"

#include "gtest/gtest.h"

class StaticEvaluationTest : public ::testing::Test {
public:
    StaticEvaluationTest() {
        game = new GameState();
    }
    
    virtual void SetUp() {
        player = new Player();
        enemy = new Player();
    }
    
    virtual void TearDown() {
    }
    GameState* game;
    Player* player;
    Player* enemy;
};

TEST_F( StaticEvaluationTest, CalculateBuildingZeroResult ) {
    std::list<Building*> playerBuildings;
    std::list<Building*> enemyBuildings;
    Building* building1 = new Building();
    Building* building2 = new Building();
    Building* building3 = new Building();
    Building* building4 = new Building();
    building1->setCaptureValue(10);
    building2->setCaptureValue(10);
    building3->setCaptureValue(10);
    building4->setCaptureValue(10);
    
    playerBuildings.push_back(building1);
    playerBuildings.push_back(building2);
    enemyBuildings.push_back(building3);
    enemyBuildings.push_back(building4);
    
    ASSERT_EQ( 0, game->calculateBuildingsHealth(playerBuildings, enemyBuildings) );
    
}
//
//  HeuristicTest.cpp
//  ProjectWar
//
//  Created by Pablo Luis Gutierrez on 02/06/16.
//  Copyright © 2016 Alvaro Chambi Campos. All rights reserved.
//

#include <stdio.h>
#include "HeuristicFunction.h"
#include "Player.h"

#include "gtest/gtest.h"

class HeuristicTest : public ::testing::Test {
public:
    HeuristicTest() {
        heuristic = new HeuristicFunction();

    }
    
    virtual void SetUp() {
        player = new Player();
        enemy = new Player();
        building1 = new Building();
        building2 = new Building();
        building3 = new Building();
        building4 = new Building();

    }
    
    virtual void TearDown() {

    }
    HeuristicFunction* heuristic;
    Player* player;
    Player* enemy;
    std::list<Building*> playerBuildings;
    std::list<Building*> enemyBuildings;
    Building* building1;
    Building* building2;
    Building* building3;
    Building* building4;
};

TEST_F( HeuristicTest, CalculateBuildingZeroResult ) {

    building1->setCaptureValue(12);
    building2->setCaptureValue(10);
    building3->setCaptureValue(10);
    building4->setCaptureValue(10);
    
    playerBuildings.push_back(building1);
    playerBuildings.push_back(building2);
    enemyBuildings.push_back(building3);
    enemyBuildings.push_back(building4);
    
    ASSERT_EQ( 0, heuristic->calculateBuildingsHealth(playerBuildings, enemyBuildings) );
    
}

TEST_F( HeuristicTest, CalculateBuildingNegativeResult ) {
    
    building1->setCaptureValue(10);
    building2->setCaptureValue(12);
    building3->setCaptureValue(10);
    building4->setCaptureValue(10);
    
    playerBuildings.push_back(building1);
    playerBuildings.push_back(building2);
    enemyBuildings.push_back(building3);
    enemyBuildings.push_back(building4);
    
    
    ASSERT_EQ( 0, heuristic->calculateBuildingsHealth(playerBuildings, enemyBuildings) );
    
}
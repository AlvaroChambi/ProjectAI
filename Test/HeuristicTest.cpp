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
    }
    
    virtual void SetUp() {
        player = new Player();
        enemy = new Player();
        heuristic = new HeuristicFunction( player, enemy );
        building1 = new Building();
        building2 = new Building();
        building3 = new Building();
        building4 = new Building();
        building1->setCapturePoints(20);
        building2->setCapturePoints(20);
        building3->setCapturePoints(20);
        building4->setCapturePoints(20);
        unit1 = new Unit;
        unit1->setHP( 10 );
        unit2 = new Unit;
        unit2->setHP( 10 );
        unit3 = new Unit;
        unit4 = new Unit;
    }
    
    virtual void TearDown() {
        building1->setCaptureValue(0);
        building2->setCaptureValue(0);
        building3->setCaptureValue(0);
        building4->setCaptureValue(0);

    }
    HeuristicFunction* heuristic;
    Player* player;
    Player* enemy;
    std::list<Building*> playerBuildings;
    std::list<Building*> enemyBuildings;
    Unit* unit1;
    Unit* unit2;
    Unit* unit3;
    Unit* unit4;
    Unit* unit5;
    Unit* unit6;
    
    Building* building1;
    Building* building2;
    Building* building3;
    Building* building4;
    Tile tile;
    Point point;
    
};

TEST_F( HeuristicTest, CalculateBuildingZeroResult ) {
    building1->setCaptureValue(10);
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
    building2->setCaptureValue(10);
    building3->setCaptureValue(12);
    building4->setCaptureValue(12);
    
    playerBuildings.push_back(building1);
    playerBuildings.push_back(building2);
    
    enemyBuildings.push_back(building3);
    enemyBuildings.push_back(building4);
    
    ASSERT_EQ( -4, heuristic->calculateBuildingsHealth(playerBuildings, enemyBuildings) );
    
}

TEST_F( HeuristicTest, CalculateBuildingPositiveResult ) {
    
    building1->setCaptureValue(12);
    building2->setCaptureValue(12);
    building3->setCaptureValue(10);
    building4->setCaptureValue(10);
    
    playerBuildings.push_back(building1);
    playerBuildings.push_back(building2);
    enemyBuildings.push_back(building3);
    enemyBuildings.push_back(building4);
    
    
    ASSERT_EQ( 4, heuristic->calculateBuildingsHealth(playerBuildings, enemyBuildings) );
}

TEST_F( HeuristicTest, CalculateHQDistanceResult ) {
    building1->setPosition( Tile( 0, 1 ) ); //playerHQ
    building2->setPosition( Tile( 2, 1 ) ); //enemyHQ
    
    unit1->setPosition( 0, 0 );
    unit2->setPosition( 2, 2 );
    
//    player->addUnit( unit2->getId() );
//    enemy->addUnit( unit1->getId() );
    
//    ASSERT_EQ( 0, heuristic->calculateEnemyHeadquarterDistance( building1, building2 ) );
}

TEST_F( HeuristicTest, CalculateHQDistanceNullHQ ) {
    building1->setPosition( Tile( 0, 1 ) ); //playerHQ
    building2->setPosition( Tile( 2, 1 ) ); //enemyHQ
    
    unit1->setPosition( 0, 0 );
    unit2->setPosition( 2, 2 );
    
//    player->addUnit( unit2->getId() );
//    enemy->addUnit( unit1->getId() );
//    
//    ASSERT_EQ( 0, heuristic->calculateEnemyHeadquarterDistance( nullptr, building2 ) );
}
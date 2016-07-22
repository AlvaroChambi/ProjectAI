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
        
    }
    
    virtual void SetUp() {
        map = new Map( player, opponent );
    }
    
    virtual void TearDown() {
    }
    
    Map* map;
    Player player;
    Player opponent;
};

TEST_F( MapTest, MapAddEntityTest ) {
    Unit* unit = new Unit;
    unit->setid( 0 );
    unit->setPosition( 1, 1 );
    
    map->addEntity( *unit );
    
    ASSERT_EQ( Point( 1, 1 ), map->getEntityReference( 0 ) );
}

TEST_F( MapTest, MapAddEntityTestOverride ) {
    Unit* unit = new Unit;
    unit->setid( 0 );
    unit->setPosition( 1, 1 );
    
    Unit* unit2 = new Unit;
    unit2->setid( 1 );
    unit2->setPosition( 1, 1 );
    
    map->addEntity( *unit );
    ASSERT_ANY_THROW( map->addEntity( *unit2 ) );
}

TEST_F( MapTest, MapAddEntitySameIDTest ) {
    Unit* unit = new Unit;
    unit->setid( 0 );
    unit->setPosition( 1, 1 );
    
    Unit* unit2 = new Unit;
    unit2->setid( 0 );
    unit2->setPosition( 0, 0 );
    
    map->addEntity( *unit );
    ASSERT_ANY_THROW( map->addEntity( *unit2 ) );
}

TEST_F( MapTest, MapMoveEntityTest ) {
    Unit* unit = new Unit;
    unit->setid( 0 );
    unit->setPosition( 1, 1 );
    
    map->addEntity( *unit );
    
    map->moveEntity( *unit, Point( 2, 2 ) );
    
    ASSERT_EQ( Point( 2, 2 ) , map->getEntityReference( unit->getId() ) );
}

TEST_F( MapTest, MapGetEntityNotFound ) {
    
    ASSERT_EQ( nullptr, map->getEntity( Point( 0, 0 ) ) );
}

TEST_F( MapTest, MapGetEntityByReference ) {
    Unit* unit = new Unit;
    unit->setid( 0 );
    unit->setPosition( 1, 1 );
    
    map->addEntity( *unit );
    
    ASSERT_EQ( unit, map->getEntity( Point( 1, 1 ) ) );
}

TEST_F( MapTest, MapGetEntityByID ) {
    Unit* unit = new Unit;
    unit->setid( 0 );
    unit->setPosition( 1, 1 );
    
    map->addEntity( *unit );
    
    ASSERT_EQ( unit, map->getEntity( 0 ) );
}

TEST_F( MapTest, MapGetEntityByIDNotFound ) {
    ASSERT_ANY_THROW( map->getEntity( 0 ) );
}
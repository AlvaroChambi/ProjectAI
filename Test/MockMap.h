//
//  MockMap.h
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 31/5/16.
//  Copyright © 2016 Alvaro Chambi Campos. All rights reserved.
//

#ifndef MockMap_h
#define MockMap_h

#include "gmock/gmock.h"
#include "MapContext.h"
#include "Player.h"

class MockMap : public  MapContext {
public:
    MOCK_CONST_METHOD0( getNumRows, int() );
    MOCK_CONST_METHOD0( getNumColumns, int() );
    
    MOCK_CONST_METHOD1( isValidPosition, bool( const Point& position ) );
    
    MOCK_CONST_METHOD1( getTile, Tile( const Point& position ) );
    
    MOCK_METHOD1( addEntity, void( Unit& unit ) );
    MOCK_CONST_METHOD1( getEntity, Unit*( const Point& reference ) );
    MOCK_CONST_METHOD1( getEntity, Unit*( int id ) );
    MOCK_CONST_METHOD1( getEntityReference, Point( int id ) );
    
    MOCK_METHOD2( moveEntity, void( Unit& unit, const Point& destination ) );
    
    MOCK_METHOD1( restoreUnit, void( Unit& unit ) );
    MOCK_METHOD1( removeUnit, void( Unit& unit ) );
    
    MOCK_METHOD1( addStructure, void( Building& building ) );
    MOCK_CONST_METHOD1( getStructure, Building*( const Point& reference ) );
    MOCK_CONST_METHOD1( getStructure, Building*( int id ) );
    MOCK_CONST_METHOD0( getStructures, std::vector<Building*>() );
    
    MOCK_CONST_METHOD0( getPlayer, const Player&() );
    MOCK_CONST_METHOD0( getOpponent, const Player&() );
    
    MOCK_CONST_METHOD1( getPlayer, const Player*( const int id ) );
};

#endif /* MockMap_h */

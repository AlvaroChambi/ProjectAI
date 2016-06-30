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
#include "IMap.h"

class MockMap : public  IMap {
public:
    MOCK_METHOD1( isValidPosition, bool( const Point& position ) );
    MOCK_METHOD2( getTile, Tile( int x, int y ) );
};

#endif /* MockMap_h */

//
//  MockMap.h
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 31/5/16.
//  Copyright © 2016 Alvaro Chambi Campos. All rights reserved.
//

#ifndef MockMap_h
#define MockMap_h

#include "Map.h"

class MockMap : public  IMap {
public:
    MOCK_METHOD2( getBoundingArea, std::pair<Point,Point>*( Point position, int range ) );
    MOCK_METHOD1( isValidPosition, bool( Point position ) );
    MOCK_METHOD2( getTile, Tile( int x, int y ) );
};

#endif /* MockMap_h */

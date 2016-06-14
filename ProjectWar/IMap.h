//
//  IMap.h
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 31/5/16.
//  Copyright © 2016 Alvaro Chambi Campos. All rights reserved.
//

#ifndef IMap_h
#define IMap_h

class IMap {
public:
    virtual std::pair<Point,Point>* getBoundingArea( Point position, int range ) = 0;
    virtual bool isValidPosition( const Point& position ) = 0;
    virtual Tile getTile( int x, int y ) = 0;
    virtual bool isOnBounds( Point position ) = 0;
};

#endif /* IMap_h */

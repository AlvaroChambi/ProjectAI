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
    std::pair<Point,Point>* getBoundingArea( Point position, int range );
    bool isValidPosition( Point position );
};

#endif /* IMap_h */

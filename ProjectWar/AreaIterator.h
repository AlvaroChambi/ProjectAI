//
//  AreaIterator.h
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 1/6/16.
//  Copyright © 2016 Alvaro Chambi Campos. All rights reserved.
//

#ifndef AreaIterator_h
#define AreaIterator_h

#include "Iterator.h"
#include "Point.h"

class AreaIterator : public Iterator {
public:
    AreaIterator();
    ~AreaIterator();
    
    void buildArea( const Point& origin, int range,
                    int maxWidth, int maxHeight );
    void setArea( const std::pair<Point, Point>& area  );
    const std::pair<Point,Point>& getArea();
    
    int getCurrentPosition();
    void setCurrentPosition( int currentPosition );
    
    const Point& getCachedPosition();
    
    bool nextPosition();
    bool hasNext();
    const Point& next();
    bool isValid( const Point& position );
    
    int getWidth() const;
    int getHeight() const;
private:
    int currentPosition;
    bool hasCached;
    Point cached;
    
    std::pair<Point, Point> area;
};

#endif /* AreaIterator_h */

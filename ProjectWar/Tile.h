//
//  Tile.h
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 13/3/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#ifndef __ProjectWar__Tile__
#define __ProjectWar__Tile__

#include <stdio.h>
#include "Texture.h"

class Tile
{
public:
    Tile();
    Tile(Texture* texture);
    virtual ~Tile();
    
    Texture* getTexture();
    void setTexture(Texture* texture);
    
    bool matchPosition(Point position);
    
    Point getPosition();
    
    Point srcPosition;
    Point destPosition;
    int width;
    int height;
    
    int row;
    int column;
private:
    Texture* texture;
};

#endif /* defined(__ProjectWar__Tile__) */

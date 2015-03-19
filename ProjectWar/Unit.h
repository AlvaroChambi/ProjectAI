//
//  Unit.h
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 13/3/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#ifndef __ProjectWar__Unit__
#define __ProjectWar__Unit__

#include <stdio.h>
#include <iostream>

#include "Model.h"
#include "Tile.h"

class Unit : public Model
{
public:
    Unit();
    virtual ~Unit();
    void setPosition(const Tile tile);
    void setPosition(int x, int y);
    Tile getTile();
    Point getPosition();
private:
    Tile tile;
    int movement;
    int hp;
};

#endif /* defined(__ProjectWar__Unit__) */

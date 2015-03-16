//
//  Player.h
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 13/3/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#ifndef __ProjectWar__Player__
#define __ProjectWar__Player__

#include <stdio.h>
#include <list>

#include "Model.h"
#include "Unit.h"
#include "Tile.h"

class Player : public Model
{
public:
    Player();
    virtual ~Player();
    void setPosition( int x, int y);
    Point getPosition();
    Tile getTile();
    void setTile(const Tile tile);
private:
    Point position;
    Tile tile;
    std::list<Unit*> units;
};

#endif /* defined(__ProjectWar__Player__) */

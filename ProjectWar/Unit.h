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
    
    void setMovement(int movement);
    int getmovement();
    
    Tile getTile();
    Point getPosition();
    
    void setActive(bool active);
    bool isActive();
    
    void setSelected(bool selected);
    bool isSelected();
    
    bool canReach(Point destination);
private:
    bool selected;
    bool active;
    Tile tile;
    int movement;
    int hp;
};

#endif /* defined(__ProjectWar__Unit__) */

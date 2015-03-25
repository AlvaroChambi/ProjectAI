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
#include "State.h"
#include "Map.h"

class Player : public Model
{
public:
    Player();
    virtual ~Player();
    void setPosition( int x, int y);
    Point getPosition();
    Tile getTile();
    void setTile(const Tile tile);
    void addUnit( Unit* unit );
    Unit* getUnit(int id);
    
    Unit* getSelectedUnit();
    void setSelectedUnit(Unit* unit);
    
    State* getState();
    void updateState(State* state);
    void setState(State* state);
    
    void setMap(Map* map);
    Map* getMap();
    
    void setActive(bool active);
    bool isActive();
private:
    Point position;
    //Now that the player has a map maybe we can remove the tile 
    Tile tile;
    //TODO Replace with linked lists!!!!
    Unit* units[20];
    int numUnits;
    
    State* state;
    //TODO Dont need to have a selected unit instance if i have a player with an active param
    Unit* selectedUnit;
    Map* map;
    bool active;
};

#endif /* defined(__ProjectWar__Player__) */

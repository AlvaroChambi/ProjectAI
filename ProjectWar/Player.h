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

#include "Model.h"
#include "Unit.h"
#include "Tile.h"
#include "State.h"
#include "List.h"
#include "InfoTile.h"

class Map;
class Player : public Model
{
public:
    Player();
    Player(int id);
    virtual ~Player();
    typedef std::vector< std::vector<InfoTile*> > InfoMap;
    
    void setPosition( int x, int y);
    Point getPosition();
    Tile getTile();
    void setTile(const Tile tile);
    void addUnit( Unit* unit );
    Unit* getUnit(int id);
    
    List<Unit*> getUnitList();
    
    Unit* getSelectedUnit();
    void setSelectedUnit(Unit* unit);
    
    State* getState();
    void updateState(State* state);
    void setState(State* state);
    
    void setMap(Map* map);
    Map* getMap();
    
    void setActive(bool active);
    bool isActive();
    
    bool hasUnit(int id);
    
    //Add units data to the info map
    void populateInfoMap(InfoMap& infoMap);
private:
    Point position;
    //Now that the player has a map maybe we can remove the tile 
    Tile tile;
    List<Unit*> units;
    
    State* state;
    //TODO Dont need to have a selected unit instance if i have a player with an active param
    Unit* selectedUnit;
    Map* map;
    bool active;
};

#endif /* defined(__ProjectWar__Player__) */

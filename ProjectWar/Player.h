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
#include "InfoTile.h"
#include "IPlayer.h"

enum PlayerType
{
    AI_PLAYER,
    HUMAN_PLAYER,
};

class Map;
class Player : public IPlayer, public Model
{
public:
    Player();
    Player(int id);
    virtual ~Player();
    typedef std::vector< std::vector<InfoTile*> > InfoMap;
    
    void setPosition( int x, int y);
    Point getPosition();
    Tile getTile() const;
    void setTile( const Tile tile );
    void addUnit( Unit* unit );
    Unit* getUnit( int id ) const;
    
    std::list<Unit*>& getUnitList();
    std::vector<Unit*>& getAliveUnits();
    
    Unit* getSelectedUnit();
    void setSelectedUnit(Unit* unit);
    
    State* getState();
    void updateState(State* state);
    void setState(State* state);
    
    void setMap(Map* map);
    Map* getMap();
    
    void setActive(bool active);
    bool isActive();
    
    PlayerType getType();
    void setType( PlayerType type );
    
    bool hasUnit(int id);
    
    //Add units data to the info map
    void populateInfoMap(InfoMap& infoMap);
    
    bool hasUnitAlive();
    
    bool hasCapturedHQ( Player* enemy );
    Building* getHeadquarter();
    void setHeadquarter( Building* headquarter );
private:
    Point position;
    Tile tile;
    std::list<Unit*> units;
    std::vector<Unit*> aliveUnits;
    
    State* state;
    Unit* selectedUnit;
    Map* map;
    bool active;
    PlayerType type;
    Building* headquarter;
};

#endif /* defined(__ProjectWar__Player__) */

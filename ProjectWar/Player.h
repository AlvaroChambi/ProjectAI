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
    Player( int id );
    Player( const Player& player );
    virtual ~Player();
    
    void addUnit( Unit& unit );
    Unit* getUnit( int id ) const;
    
    std::vector<Unit*> getUnits() const;
    
    Unit* getSelectedUnit() const;
    void setSelectedUnit( Unit* unit );
    
    State* getState() const;
    void updateState( State* state );
    void setState( State* state );
    
    void setMap( Map* map );
    Map* getMap() const;
    
    void setActive( bool active );
    bool isActive() const;
    
    PlayerType getType() const;
    void setType( PlayerType type );
    
    bool hasUnit( int id ) const;
    
    bool hasUnitAlive() const;
    
    bool hasCapturedHQ( const Player& enemy ) const;
    Building* getHeadquarter() const;
    void setHeadquarter( int id );
    
    std::vector<Building*> getStructures() const;
private:
    State* state;
    Unit* selectedUnit;
    Map* map;
    bool active;
    PlayerType type;
    
    int headquarter;
    std::vector<int> army;
};

#endif /* defined(__ProjectWar__Player__) */

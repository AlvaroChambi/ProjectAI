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
#include <list>
#include <vector>

#include "Model.h"
#include "Tile.h"
#include "InfoTile.h"
#include "Action.h"
#include "Building.h"

class Player;
enum UnitCommand {
    CANCEL,
    WAIT,
    ATTACK,
    CAPTURE,
    END,
};

class Unit : public Model
{
public:
    Unit();
    Unit( const Unit& unit );
    virtual ~Unit();
    void setPosition( const Tile tile );
    void setPosition( int x, int y );
    
    void setMovement( int movement );
    int getMovement() const;
    
    Tile getTile() const;
    const Point getPosition() const;
    
    void setActive( bool active );
    bool isActive() const;
    
    void setSelected( bool selected );
    bool isSelected() const;
    
    void setAttackRange( int attackRange );
    int getAttackRange() const;
    
    void setHP( int hp );
    int getHP() const;
    
    //update his state whether is alive(set visible) or is dead(set visible false)
    void updateState();
    
    void addCommand( UnitCommand command );
    UnitCommand getCommand( int position ) const;
    void updateCommands( std::vector<UnitCommand> commands );
    
    int getNumCommands() const;
    
    void setOwnerID( int ownerID );
    int getOwnerID() const;
private:
    Tile tile;
    int movement;
    int hp;
    int attackRange;
    int ownerID;
    
    std::vector<UnitCommand> commands;
    std::vector<Action*> actions;
    bool selected;
    bool active;
};

#endif /* defined(__ProjectWar__Unit__) */

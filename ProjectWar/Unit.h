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
#include "List.h"
#include "InfoTile.h"

enum UnitCommand
{
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
    virtual ~Unit();
    void setPosition(const Tile tile);
    void setPosition(int x, int y);
    
    void setMovement(int movement);
    int getMovement();
    
    Tile getTile();
    Point getPosition();
    
    void setActive(bool active);
    bool isActive();
    
    void setSelected(bool selected);
    bool isSelected();
    
    void setAttackRange(int attackRange);
    int getAttackRange();
    
    void setHP(int hp);
    int getHP();
    
    //update his state whether is alive(set visible) or is dead(set visible false)
    void updateState();
    
    void addCommand(UnitCommand command);
    UnitCommand getCommand(int position);
    void updateCommands(List<UnitCommand> commands);
    
    int getNumCommands();
    
    bool canReach(Point destination);
    bool canAttack(Point destination);
    bool canAttack(Unit* unit);
private:
    bool selected;
    bool active;
    Tile tile;
    int movement;
    int hp;
    int attackRange;
    List<UnitCommand> commands;
};

#endif /* defined(__ProjectWar__Unit__) */

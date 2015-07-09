//
//  State.h
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 19/3/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#ifndef ProjectWar_State_h
#define ProjectWar_State_h
#include <iostream>

#include "Tile.h"
#include "Model.h"
#include "Unit.h"

enum Input
{
    UNIT_CLICKED,
    ENEMY_UNIT_CLICKED,
    MAP_CLICKED,
    CANCEL_CLICKED,
    WAIT_CLICKED,
    ATTACK_CLICKED,
    CAPTURE_CLICKED,
    BUILDING_CLICKED,
    UI_COMPONENT_CLICKED,
    NOT_HANDLED,
};

class State
{
public:
    State(Model* model) : model(model)
    {
    
    }
    virtual ~State()
    {
    
    }
    virtual void handleInput(Input input, int id, Tile position) = 0;
    //TODO Maybe implement a bundle and a way to serialize objects...
    virtual void handleInput(Input input, int id, Tile position, Unit*targetUnit){}
    virtual void enter() = 0;
protected:
    Model* model;
};

#endif

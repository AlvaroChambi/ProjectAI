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

enum Input
{
    UNIT_CLICKED,
    MAP_CLICKED
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
    virtual void enter() = 0;
protected:
    Model* model;
};

#endif

//
//  NothingSelectedState.h
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 19/3/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#ifndef __ProjectWar__NothingSelectedState__
#define __ProjectWar__NothingSelectedState__

#include <stdio.h>
#include "State.h"
#include "Player.h"
#include "UnitSelectedState.h"

class NothingSelectedState : public State
{
public:
    NothingSelectedState(Player* player);
    virtual ~NothingSelectedState();
    
    void enter();
    void handleInput(Input input, int id, Tile position);
};

#endif /* defined(__ProjectWar__NothingSelectedState__) */

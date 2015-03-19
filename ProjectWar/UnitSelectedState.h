//
//  UnitSelectedState.h
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 19/3/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#ifndef __ProjectWar__UnitSelectedState__
#define __ProjectWar__UnitSelectedState__

#include <stdio.h>
#include "State.h"
#include "Player.h"
#include "NothingSelectedState.h"

class UnitSelectedState : public State
{
public:
    UnitSelectedState(Player* player);
    virtual ~UnitSelectedState();
    
    void enter();
    void handleInput(Input input, int id, Tile position);
};

#endif /* defined(__ProjectWar__UnitSelectedState__) */

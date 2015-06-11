//
//  FactorySelectedState.h
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 11/6/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#ifndef __ProjectWar__FactorySelectedState__
#define __ProjectWar__FactorySelectedState__

#include <stdio.h>
#include "Player.h"

class FactorySelectedState : public State
{
public:
    FactorySelectedState(Player* player);
    virtual ~FactorySelectedState();
    
    void enter();
    void handleInput(Input input, int id, Tile position);

};

#endif /* defined(__ProjectWar__FactorySelectedState__) */

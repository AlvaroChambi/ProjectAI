//
//  OnAttackState.h
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 29/3/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#ifndef __ProjectWar__OnAttackState__
#define __ProjectWar__OnAttackState__

#include <stdio.h>
#include "OnCommandState.h"

class OnAttackState: public OnCommandState
{
public:
    OnAttackState(Model* model, State* savedState);
    virtual ~OnAttackState();
    void handleInput(Input input, int id, Tile position);
    void handleInput(Input input, int id, Tile position, Unit* unit);
    void enter();
private:
    Unit* targetUnit;
};

#endif /* defined(__ProjectWar__OnAttackState__) */

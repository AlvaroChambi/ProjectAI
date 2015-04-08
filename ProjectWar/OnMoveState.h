//
//  OnMoveState.h
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 29/3/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#ifndef __ProjectWar__OnMoveState__
#define __ProjectWar__OnMoveState__

#include <stdio.h>
#include "OnCommandState.h"

class OnMoveState : public OnCommandState
{
public:
    OnMoveState(Model* model, State* savedState, Command* command);
    virtual ~OnMoveState();
    void handleInput(Input input, int id, Tile position);
    void enter();
};

#endif /* defined(__ProjectWar__OnMoveState__) */

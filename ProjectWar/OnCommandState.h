//
//  OnCommandState.h
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 29/3/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#ifndef __ProjectWar__OnCommandState__
#define __ProjectWar__OnCommandState__

#include <stdio.h>
#include "State.h"
#include "Command.h"

class OnCommandState : public State
{
public:
    OnCommandState(Model* model, Command* Command);
    virtual ~OnCommandState();
    virtual void handleInput(Input input, int id, Tile position);
    virtual void enter() = 0;
private:
    State* savedState;
    Command* command;
};

#endif /* defined(__ProjectWar__OnCommandState__) */

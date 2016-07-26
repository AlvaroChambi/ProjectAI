//
//  Action.h
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 01/06/16.
//  Copyright (c) 2016 Alvaro Chambi Campos. All rights reserved.
//

#ifndef ProjectWar_Action_h
#define ProjectWar_Action_h

#include <vector>
#include "Command.h"

/**
 * Unit action, can be a move, attack or capture action
 * capture and attack actions also includes a move command
 */
class Action {
public:
    Action();
    Action( int score ) : score( score ) {
        
    }
    ~Action();
    
    void execute();
    void cancel();
    
    std::vector<Command*> commands;
    int score;
};

#endif

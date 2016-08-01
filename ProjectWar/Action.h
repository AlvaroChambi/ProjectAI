//
//  Action.h
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 01/06/16.
//  Copyright (c) 2016 Alvaro Chambi Campos. All rights reserved.
//

#ifndef ProjectWar_Action_h
#define ProjectWar_Action_h

#include "Point.h"
#include "ActionEvaluator.h"

#include <vector>

/**
 * Unit action, can be a move, attack or capture action
 * capture and attack actions also includes a move command
 */
class MoveCommand;
class Command;
class Action {
public:
    Action();
    Action( int score ) : score( score ) {
        
    }
    ~Action();
    
    void execute();
    void cancel();
    
    float getValue( const ActionEvaluator&  evaluator,
                    const MapContext& context ) const;
    
    bool operator==( const Action& action ) const ;
    
    MoveCommand* moveCommand;
    Command* command;

    int score;
};

#endif

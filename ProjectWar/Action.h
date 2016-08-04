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
#include "Evaluator.h"

#include <vector>

/**
 * Unit action, can be a move, attack or capture action
 * capture and attack actions also includes a move command
 */
class MoveCommand;
class Command;

const static float NULL_SCORE = -1.0;

class Action {
public:
    
    Action();
    
    ~Action();
    
    void execute();
    void cancel();
    
    float getValue( const Evaluator&  evaluator,
                    const MapContext& context );
    
    bool operator==( const Action& action ) const ;
    
    MoveCommand* moveCommand;
    Command* command;

    float score;
};

struct Compare {
    Compare( const Evaluator& evaluator, const MapContext& context )
    : evaluator( evaluator ), context( context ) {
    
    }
    inline bool operator() ( Action* lh, Action* rh ) {
        return ( lh->getValue( evaluator, context ) >
                    rh->getValue( evaluator, context ) );
    }
    
    const Evaluator& evaluator;
    const MapContext& context;
};

#endif

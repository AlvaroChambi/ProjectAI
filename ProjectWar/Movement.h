//
//  Movement.h
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 22/4/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#ifndef __ProjectWar__Movement__
#define __ProjectWar__Movement__

#include <vector>

#include "Action.h"
#include "Option.h"

class Movement : public Option {
public:
    Movement();
    Movement( int numActions );
    void execute();
    void cancel();
    virtual ~Movement();
    
    void reserve( int numActions );
    bool addAction( Action& action );
    bool contains( const Action& action ) const;
    
    const std::vector<Action*>& getActions() const;
private:
    std::vector<Action*> actions;
};

#endif /* defined(__ProjectWar__Movement__) */

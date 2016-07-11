//
//  ActionBuilder.h
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 11/7/16.
//  Copyright © 2016 Alvaro Chambi Campos. All rights reserved.
//

#ifndef ActionBuilder_h
#define ActionBuilder_h

#include "Action.h"

class ActionBuilder {
public:
    ActionBuilder( int size );
    
    void append(  );
private:
    std::vector<Action*> vector;
};

#endif /* ActionBuilder_h */

//
//  ActionFactory.h
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 12/07/16.
//  Copyright (c) 2016 Alvaro Chambi Campos. All rights reserved.
//

#ifndef ProjectWar_ActionFactory_h
#define ProjectWar_ActionFactory_h

#include "Action.h"

enum ActionType {
    ATTACK_ACTION,
    CAPTURE_ACTION,
    MOVE_ACTION;
}

class ActionFactory {
public:
    virtual Action& createAction( const ActionType& actionType );
};

#endif

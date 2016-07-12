//
//  EntityActionFactory.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 12/07/16.
//  Copyright (c) 2016 Alvaro Chambi Campos. All rights reserved.
//

#include "EntityActionFactory.h"

Action& EntityActionFactory::createAction( const ActionType &actionType ) {
    switch ( actionType ) {
        case MOVE_ACTION:
            break;
        case ATTACK_ACTION:
            break;
        case CAPTURE_ACTION:
            break;
        default:
            break;
    }
    
}

//
//  EntityActionFactory.h
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 12/07/16.
//  Copyright (c) 2016 Alvaro Chambi Campos. All rights reserved.
//

#ifndef ProjectWar_EntityActionFactory_h
#define ProjectWar_EntityActionFactory_h

#include "ActionFactory.h"

class EntityActionFactory : public ActionFactory {
public:
    Action& createAction( const ActionType& actionType );
};

#endif

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
#include "Unit.h"

class EntityActionFactory : public ActionFactory {
public:
    void appendActions( const Unit& unit, const Unit& target,
                        std::vector<Action*>& actions );
};

#endif

//
//  IPlayerEventsListener.h
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 18/3/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#ifndef __ProjectWar__IPlayerEventsListener__
#define __ProjectWar__IPlayerEventsListener__

#include <stdio.h>
#include "Tile.h"
#include "Unit.h"

class IPlayerEventsListener
{
public:
    virtual void onUnitClicked(const int id) = 0;
    virtual void onEnemyUnitClicked(Unit* targetUnit) = 0;
    virtual void onMapClicked(const Tile tile) = 0;
};

#endif /* defined(__ProjectWar__IPlayerEventsListener__) */

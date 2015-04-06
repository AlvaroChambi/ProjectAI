//
//  InfoTile.h
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 27/3/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#ifndef __ProjectWar__InfoTile__
#define __ProjectWar__InfoTile__

#include <stdio.h>
#include "Text.h"

enum Entity
{
    NOT_DEFINED,
    UNIT_ENTITY,
    BUILDING_ENTITY,
};

class InfoTile
{
public:
    InfoTile() : entity(NOT_DEFINED), ownerID(-1), text(new Text)
    {}
    InfoTile(Entity entity, int ownerID) : entity(entity), ownerID(ownerID), text(new Text)
    {}
    virtual ~InfoTile(){}
    Entity entity;
    int ownerID;
    Text* text;
};

#endif /* defined(__ProjectWar__InfoTile__) */

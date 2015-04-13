//
//  SpriteFactory.h
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 17/3/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#ifndef __ProjectWar__SpriteFactory__
#define __ProjectWar__SpriteFactory__

#include <stdio.h>
#include "UnitView.h"
#include "PlayerView.h"

enum SpriteType
{
    UNIT,
    PLAYER,
    BUILDING,
};

//TODO Make sprite factory a static class 
class SpriteFactory
{
public:
    SpriteFactory();
    virtual ~SpriteFactory();
    Sprite* createSprite( SpriteType type );
private:
    int idCount;
};

#endif /* defined(__ProjectWar__SpriteFactory__) */

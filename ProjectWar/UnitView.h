//
//  UnitView.h
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 17/3/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#ifndef __ProjectWar__UnitView__
#define __ProjectWar__UnitView__

#include <stdio.h>

#include "Unit.h"
#include "Sprite.h"

class UnitView : public Sprite
{
public:
    UnitView();
    virtual ~UnitView();
    void setModel(Model* model);
    void update( Update update );
    void render( Renderer* renderer );
private:
    Unit* unit;
    Text* text;
};

#endif /* defined(__ProjectWar__UnitView__) */

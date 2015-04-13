//
//  BuildingView.h
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 11/4/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#ifndef __ProjectWar__BuildingView__
#define __ProjectWar__BuildingView__

#include <stdio.h>
#include "Building.h"
#include "Sprite.h"
#include "Text.h"

class BuildingView : public Sprite
{
public:
    BuildingView();
    virtual ~BuildingView();
    void setModel(Model* model);
    void update( Update update );
    void render(Renderer* renderer);
    
    void updateBuildingOwner();
private:
    Building* building;
    Text* text;
};

#endif /* defined(__ProjectWar__BuildingView__) */

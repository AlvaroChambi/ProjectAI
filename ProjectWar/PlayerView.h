
//
//  PlayerView.h
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 13/3/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#ifndef __ProjectWar__PlayerView__
#define __ProjectWar__PlayerView__

#include <stdio.h>
#include "View.h"
#include "Player.h"
#include "Sprite.h"

class PlayerView : public Sprite
{
public:
    PlayerView();
    virtual ~PlayerView();
    void setModel(Model* model);
    void update();
private:
    Player* player;
};

#endif /* defined(__ProjectWar__PlayerView__) */

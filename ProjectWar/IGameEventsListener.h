//
//  IGameEventsListener.h
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 12/3/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#ifndef ProjectWar_IGameEventsListener_h
#define ProjectWar_IGameEventsListener_h

#include "Tile.h"
#include "Sprite.h"

class IGameEventsListener
{
public:
    virtual void onTextureClicked(const Texture texture) = 0;
    virtual void onSpriteClicked(const int id) = 0;
    virtual void onSceneClicked(const Point position) = 0;
    virtual void onMapClicked(const Tile tile) = 0;
};

#endif

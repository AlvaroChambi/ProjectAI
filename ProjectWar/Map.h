//
//  Map.h
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 13/3/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#ifndef __ProjectWar__Map__
#define __ProjectWar__Map__

#include <stdio.h>
#include <vector>
#include "Texture.h"
#include "Renderer.h"
#include "SDLTexture.h"
#include "Tile.h"
#include "Unit.h"

static const int MAP_WIDTH = 15;
static const int MAP_HEIGHT = 10;
class Map
{
public:
    Map();
    virtual ~Map();
    //Width and height in tiles
    void loadMap(Renderer* renderer, int width, int height);
    void drawMap(Renderer* renderer);
    Tile* matchEvent(Point position);
    //cast tile map position to absolute window coordinate position
    Point getAbsolutePosition(Point tilePosition);
    Point getAbsolutePosition(int x, int y);
    
    Tile getTile(int x, int y);
    
    void updateUnitAvailableArea(Unit* unit);
    void cleanUnitAvailableArea(Unit* unit);
private:
    std::vector< std::vector<Tile*> > matrix;
};

#endif /* defined(__ProjectWar__Map__) */

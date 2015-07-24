//
//  MapBuilder.h
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 9/7/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#ifndef __ProjectWar__MapBuilder__
#define __ProjectWar__MapBuilder__

#include <stdio.h>
#include "Map.h"

class MapBuilder
{

public:
    MapBuilder();
    ~MapBuilder();
    
    std::vector<Tile*> buildMap(std::string mapScript);
    Tile* buildTile(int tileCode, int position);
    
    int rows;
    int columns;
    
    int spacing;
    int margin;
    
    int tileWidth;
    int tileHeight;
    
    int imageWidth;
    int imageHeight;
    
    std::string resource;
    std::vector<int> mapLayout;
};

#endif /* defined(__ProjectWar__MapBuilder__) */

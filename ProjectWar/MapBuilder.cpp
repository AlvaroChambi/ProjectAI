//
//  MapBuilder.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 9/7/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#include "MapBuilder.h"
#include "LuaScript.h"

MapBuilder::MapBuilder()
{

}

MapBuilder::~MapBuilder()
{

}

std::vector<Tile*> MapBuilder::buildMap(std::string mapScript)
{
    LuaScript script(mapScript);
    
    resource = script.get<std::string>("map.resource");
    
    columns = script.get<int>("map.columns");
    rows = script.get<int>("map.rows");
    margin = script.get<int>("map.margin");
    spacing = script.get<int>("map.spacing");
    
    tileWidth = script.get<int>("map.tile_width");
    tileHeight = script.get<int>("map.tile_height");
    
    imageWidth = script.get<int>("map.image_width");
    imageHeight = script.get<int>("map.image_height");
    
    mapLayout = script.getIntVector("map.map_layout");
    std::vector<Tile*> mapTiles;
    
    int position = 0;
    for (int tileCode : mapLayout) {
        Tile* tile = buildTile(tileCode, position++);
        //Add a tile to the map
        mapTiles.push_back(tile);
    }
    return mapTiles;
}

Tile* MapBuilder::buildTile(int tileCode, int position)
{
    Tile* tile = new Tile;
    tile->width = tileWidth;
    tile->height = tileHeight;
    int imageColumns = imageWidth / tileWidth;
    //int imageRows = imageHeight / tileHeight;
    
    int textureRow = tileCode / imageColumns;
    int textureColumn = tileCode % imageColumns;
    
    int actualRow = position / columns;
    int actualColumn = position % columns;
    
    tile->srcPosition.x = margin + (textureColumn * tileWidth) + (textureColumn * spacing);
    tile->srcPosition.y = margin + (textureRow * tileHeight) + (textureRow * spacing);
    
    int destX = actualColumn * tile->width;
    int destY = actualRow * tile->height;
    
    tile->destPosition = Point(destX, destY);
    
    tile->column = actualColumn;
    tile->row = actualRow;
    
    return tile;
}



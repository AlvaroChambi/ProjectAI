//
//  Map.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 13/3/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#include "Map.h"

Map::Map()
{
    matrix.resize(MAP_WIDTH);
    for(int i = 0; i < MAP_WIDTH; i++){
        matrix.at(i).resize(MAP_HEIGHT, 0);
    }
}

Map::~Map()
{

}

//Using static map width and height for now
void Map::loadMap(Renderer* renderer, int width, int height)
{
    for(int i = 0; i < MAP_WIDTH ; i++){
        int posX = i * width;
        for(int j = 0; j < MAP_HEIGHT ; j++){
            int posY = j * height;
            //use static color !Change this¡
            Color color = Color(0,153,0);
            Texture * texture = renderer->loadShape(RECTANGLE, color,width, height);
            texture->setPosition(posX, posY);
            Tile* tile = new Tile(texture);
            tile->position.x = i;
            tile->position.y = j;
            matrix[i][j] = tile;
        }
    }
}

void Map::drawMap(Renderer* renderer)
{
    for(int i = 0; i < MAP_WIDTH; i++){
        for(int j = 0; j < MAP_HEIGHT; j++){
            renderer->drawTexture(matrix[i][j]->getTexture());
        }
    }
}

Tile* Map::matchEvent(Point position)
{
    Tile* tile = nullptr;
    for (int i = 0; i < MAP_WIDTH; i++) {
        for (int j = 0; j < MAP_HEIGHT ; j++) {
            if(matrix[i][j]->getTexture()->matchPosition(position)){
                tile = matrix[i][j];
            }
        }
    }
    return tile;
}

Point Map::getAbsolutePosition(Point tilePosition)
{
    Point point;
    if (tilePosition.x < MAP_WIDTH && tilePosition.y < MAP_HEIGHT) {
        point = matrix[tilePosition.x][tilePosition.y]->getTexture()->getPosition();
    }
    return point;
}

Point Map::getAbsolutePosition(int x, int y)
{
    Point point;
    point.x = x;
    point.y = y;
    return getAbsolutePosition(point);
}

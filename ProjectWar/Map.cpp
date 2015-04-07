//
//  Map.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 13/3/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#include "Map.h"
#include "Player.h"
#include <iostream>

Map::Map()
{
    infoMap.resize(MAP_WIDTH);
    matrix.resize(MAP_WIDTH);
    for(int i = 0; i < MAP_WIDTH; i++){
        matrix.at(i).resize(MAP_HEIGHT, 0);
        infoMap.at(i).resize(MAP_HEIGHT);
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

//pretty much the same code herer and in the updateUnitAvailableArea method...
//We can also have always referenced the updated tiles in the map, so we can clean them whenever we want

void Map::cleanUnitAvailableArea(Unit *unit)
{
    int x = unit->getPosition().x - unit->getmovement();
    int y = unit->getPosition().y - unit->getmovement();
    
    for (int i = x; i <= x + (unit->getmovement() * 2) ; i++) {
        for (int j = y; j <= y + (unit->getmovement() * 2); j++) {
            int distance = std::abs(unit->getPosition().x - i) + std::abs(unit->getPosition().y - j);
            if(distance >= 0 && distance <= unit->getmovement()){
                //TODO Update tile of the [i][j] position, just hiding tiles now...
                //maybe create a tile pool and draw a new one for each position
                
                if( i >= 0 && i < MAP_WIDTH && j >= 0 && j < MAP_HEIGHT){ //Avoiding negative and outside map positions
                    matrix[i][j]->getTexture()->setVisible(true);
                }
            }
        }
    }
}

void Map::updateUnitAvailableArea(Unit *unit)
{
    int x = unit->getPosition().x - unit->getmovement();
    int y = unit->getPosition().y - unit->getmovement();
    
    for (int i = x; i <= x + (unit->getmovement() * 2) ; i++) {
        for (int j = y; j <= y + (unit->getmovement() * 2) ; j++) {
            int distance = std::abs(unit->getPosition().x - i) + std::abs(unit->getPosition().y - j);
            if(distance >= 0 && distance <= unit->getmovement()){
                //TODO Update tile of the [i][j] position, just hiding tiles now...
                //maybe create a tile pool and draw a new one for each position
                
                if( i >= 0 && i < MAP_WIDTH && j >= 0 && j < MAP_HEIGHT ){ //Avoiding negative and outside map positions
                    matrix[i][j]->getTexture()->setVisible(false);
                }
            }
        }
    }
}

void Map::drawMap(Renderer* renderer)
{
    for(int i = 0; i < MAP_WIDTH; i++){
        for(int j = 0; j < MAP_HEIGHT; j++){
            if(matrix[i][j]->getTexture()->isVisible()){
                renderer->drawTexture(matrix[i][j]->getTexture());
            }
        }
    }
}

void Map::drawInfoMap(Renderer *renderer)
{
    //Draws info map over the map
    for(int i = 0; i < MAP_WIDTH; i++){
        for(int j = 0; j < MAP_HEIGHT; j++){
            InfoTile* tile = infoMap[i][j];
            tile->text->render(renderer);
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

Tile Map::getTile(int x, int y)
{
    return *matrix[x][y];
}

void Map::loadInfoMap(List<Player *> &players)
{
    for(int i = 0; i < MAP_WIDTH; i++){
        for(int j = 0; j < MAP_HEIGHT; j++){
            infoMap[i][j] = new InfoTile();
        }
    }
    for (int i = 0; i < players.getSize(); i++ ) {
        players.getElement(i)->populateInfoMap(infoMap);
    }
    //Creating a texture for each defined text" entity : owner"
    for(int i = 0; i < MAP_WIDTH; i++){
        for(int j = 0; j < MAP_HEIGHT; j++){
            InfoTile* tile = infoMap[i][j];
            switch (tile->entity) {
                case UNIT_ENTITY:
                {
                    tile->text->setPosition(this->getAbsolutePosition(i, j));
                    break;
                }
                default:
                    break;
            }
        }
    }
}

Map::InfoMap& Map::getInfoMap()
{
    return infoMap;
}

void Map::checkNearEntities(Unit *unit, List<UnitCommand>& commands)
{
    InfoTile* unitTile = infoMap[unit->getPosition().x][unit->getPosition().y];
    int x = unit->getPosition().x - unit->getAttackRange();
    int y = unit->getPosition().y - unit->getAttackRange();
    
    for (int i = x; i <= x + (unit->getAttackRange() * 2) ; i++) {
        for (int j = y; j <= y + (unit->getAttackRange() * 2) ; j++) {
            int distance = std::abs(unit->getPosition().x - i) + std::abs(unit->getPosition().y - j);
            if(distance >= 0 && distance <= unit->getAttackRange() && i >= 0 && j >= 0){
                if(i >= 0 && i < MAP_WIDTH && j >= 0 && j < MAP_HEIGHT){
                    InfoTile* infoTile = infoMap[i][j];
                    
                    if(infoTile->ownerID != -1 && infoTile->ownerID != unitTile->ownerID){
                        commands.add(ATTACK);
                    }
                }
            }
        }
    }
}

void Map::moveUnit(Unit *unit, Point destination){
    InfoTile* tile = infoMap[unit->getPosition().x][unit->getPosition().y];
    InfoTile* destinationTile = infoMap[destination.x][destination.y];
    int ownerID = tile->ownerID;
    //clean tile
    tile->text->setTextResource("");
    tile->ownerID = -1;
    //update new tile
    destinationTile->ownerID = ownerID;
    destinationTile->text->setTextResource("Unit: " + std::to_string(destinationTile->ownerID));
    destinationTile->text->setPosition(this->getAbsolutePosition(destination));
}

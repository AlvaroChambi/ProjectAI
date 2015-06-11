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
#include "Path.h"
#include "Pathfinder.h"
#include "BuildingFactory.h"

Map::Map()
{
    infoMap.resize(MAP_WIDTH);
    matrix.resize(MAP_WIDTH);
    for(int i = 0; i < MAP_WIDTH; i++){
        matrix.at(i).resize(MAP_HEIGHT, 0);
        infoMap.at(i).resize(MAP_HEIGHT);
    }
    pathfinder = new Pathfinder(this);
}

Map::~Map()
{

}

void Map::addBuilding(Building *building)
{
    buildings.push_back(building);
}

Building* Map::getBuilding(int id)
{
    Building* result = nullptr;
    for (Building* building : buildings) {
        if(building->getId() == id){
            result = building;
        }
    }
    return result;
}

std::list<Building*>& Map::getBuildings()
{
    return buildings;
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

void Map::loadBuildings(SpriteFactory* spriteFactory, Renderer* renderer)
{
    BuildingFactory factory = BuildingFactory();
    
    Building* building = factory.createBuilding("headquarter.lua");
    Sprite* buildingSprite = spriteFactory->createSprite(BUILDING);
    buildingSprite->setModel(building);
    buildingSprite->setTexture(renderer->loadSprite(building->getResource(), 64, 64));
    buildingSprite->resize(40, 40);
    building->setPosition(getTile(2, 2));
    building->setOwnerID(0);
    this->addBuilding(building);
    
    Building* building2 = factory.createBuilding("headquarter.lua");
    Sprite* buildingSprite2 = spriteFactory->createSprite(BUILDING);
    buildingSprite2->setModel(building2);
    buildingSprite2->setTexture(renderer->loadSprite(building2->getResource(), 64, 64));
    buildingSprite2->resize(40, 40);
    building2->setPosition(getTile(12,6));
    building2->setOwnerID(1);
    this->addBuilding(building2);
    
    Building* factory1 = factory.createBuilding("factory.lua");
    Sprite* factorySprite = spriteFactory->createSprite(BUILDING);
    factorySprite->setModel(factory1);
    factorySprite->setTexture(renderer->loadSprite(factory1->getResource(), 64, 64));
    factorySprite->resize(40, 40);
    factory1->setPosition(getTile(3, 4));
    factory1->setOwnerID(0);
    this->addBuilding(factory1);
    
    Building* city = factory.createBuilding("city.lua");
    Sprite* citySprite = spriteFactory->createSprite(BUILDING);
    citySprite->setModel(city);
    citySprite->setTexture(renderer->loadSprite(city->getResource(), 64, 64));
    citySprite->resize(40, 40);
    city->setPosition(getTile(8, 8));
    city->setOwnerID(0);
    this->addBuilding(city);
    
    //Add all sprite to the scene?
    sprites.push_back(citySprite);
    sprites.push_back(buildingSprite);
    sprites.push_back(buildingSprite2);
    sprites.push_back(factorySprite);
}

Building* Map::getBuilding(Point position)
{
    Building* result = nullptr;
    for (Building* building : buildings) {
        if (building->getPosition() == position) {
            result = building;
        }
    }
    return result;
}

//pretty much the same code here and in the updateUnitAvailableArea method...
//We can also have always referenced the updated tiles in the map, so we can clean them whenever we want

void Map::cleanUnitAvailableArea(Unit *unit)
{
    int x = unit->getPosition().x - unit->getMovement();
    int y = unit->getPosition().y - unit->getMovement();
    
    for (int i = x; i <= x + (unit->getMovement() * 2) ; i++) {
        for (int j = y; j <= y + (unit->getMovement() * 2); j++) {
            int distance = std::abs(unit->getPosition().x - i) + std::abs(unit->getPosition().y - j);
            if(distance >= 0 && distance <= unit->getMovement()){
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
    int x = unit->getPosition().x - unit->getMovement();
    int y = unit->getPosition().y - unit->getMovement();
    
    for (int i = x; i <= x + (unit->getMovement() * 2) ; i++) {
        for (int j = y; j <= y + (unit->getMovement() * 2) ; j++) {
            int distance = std::abs(unit->getPosition().x - i) + std::abs(unit->getPosition().y - j);
            if(distance >= 0 && distance <= unit->getMovement()){
                //TODO Update tile of the [i][j] position, just hiding tiles now...
                //maybe create a tile pool and draw a new one for each position
                
                if( i >= 0 && i < MAP_WIDTH && j >= 0 && j < MAP_HEIGHT ){ //Avoiding negative and outside map positions
                    matrix[i][j]->getTexture()->setVisible(false);
                }
            }
        }
    }
}

void Map::drawMap(Renderer* renderer, Camera* camera)
{
    for(int i = 0; i < MAP_WIDTH; i++){
        for(int j = 0; j < MAP_HEIGHT; j++){
            if(matrix[i][j]->getTexture()->isVisible()){
                //TODO Debug, change the way to implement the camera
                //TODO just draw if the texture is on the camera area
                renderer->drawTexture(matrix[i][j]->getTexture());
            }
        }
        
    }
    
    for (Sprite* sprite : sprites) {
        sprite->render(renderer);
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

int Map::matchSpriteEvent(Point position)
{
    int id = -1;
    for (Sprite* sprite: sprites) {
        if (sprite->matchPosition(position)) {
            id = sprite->getID();
        }
    }
    return id;
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

Tile Map::getTile(Point point)
{
    return getTile(point.x, point.y);
}


void Map::hideTile(Point position)
{
    Tile* tile = matrix[position.x][position.y];
    tile->getTexture()->setVisible(false);
}

InfoTile& Map::getInfoTile(Point position)
{
    return *infoMap[position.x][position.y];
}

bool Map::isValidPosition(Point position)
{
    bool result = false;
    if (position.x >= 0 && position.x < MAP_WIDTH
            && position.y >= 0 && position.y < MAP_HEIGHT) {
        InfoTile tile = getInfoTile(position);
        result = true;
        /* Avoiding unit checking at this point
        if (tile.entity != UNIT_ENTITY) {
            result = true;
        }*/

    }
    return result;
}

void Map::loadInfoMap(std::list<Player *> &players)
{
    for(int i = 0; i < MAP_WIDTH; i++){
        for(int j = 0; j < MAP_HEIGHT; j++){
            infoMap[i][j] = new InfoTile();
        }
    }
    for (Player* player : players) {
        player->populateInfoMap(infoMap);
    }
    
    for (Building* building : buildings) {
        InfoTile* tile = infoMap[building->getPosition().x][building->getPosition().y];
        tile->entity = BUILDING_ENTITY;
        tile->ownerID = building->getOwnerID();
        tile->text->setTextResource("Build.: " + std::to_string(tile->ownerID));
    }
    
    //Placing the tiles in his absolute position(maybe we could avoid this...)
    for(int i = 0; i < MAP_WIDTH; i++){
        for(int j = 0; j < MAP_HEIGHT; j++){
            InfoTile* tile = infoMap[i][j];
            switch (tile->entity) {
                case UNIT_ENTITY:
                case BUILDING_ENTITY:
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

void Map::checkNearEntities(Unit *unit, std::list<UnitCommand>& commands)
{
    InfoTile* unitTile = infoMap[unit->getPosition().x][unit->getPosition().y];
    int x = unit->getPosition().x - unit->getAttackRange();
    int y = unit->getPosition().y - unit->getAttackRange();
    //TODO Change this, think another way to setop searching near unit when we have already found one
    bool commandAdded = false;
    
    for (int i = x; i <= x + (unit->getAttackRange() * 2) ; i++) {
        for (int j = y; j <= y + (unit->getAttackRange() * 2) ; j++) {
            int distance = std::abs(unit->getPosition().x - i) + std::abs(unit->getPosition().y - j);
            if(distance >= 0 && distance <= unit->getAttackRange() && i >= 0 && j >= 0){
                if(i >= 0 && i < MAP_WIDTH && j >= 0 && j < MAP_HEIGHT){
                    InfoTile* infoTile = infoMap[i][j];
                    
                    if(infoTile->ownerID != -1 && infoTile->ownerID != unitTile->ownerID
                       && !commandAdded){
                        commands.push_back(ATTACK);
                        commandAdded = true;
                    }
                }
            }
        }
    }
    if (unitTile->entity == BUILDING_ENTITY) {
        commands.push_back(CAPTURE);
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
    destinationTile->unitID = unit->getId();
    destinationTile->text->setTextResource(
                "Unit: " +
                std::to_string(destinationTile->ownerID)+
                "-"+
                std::to_string(destinationTile->unitID));
    destinationTile->text->setPosition(this->getAbsolutePosition(destination));
}

void Map::removeUnit(Unit *unit)
{
    InfoTile* unitTile = infoMap[unit->getPosition().x][unit->getPosition().y];
    unitTile->cleanTile();
}

Path* Map::getPath(Point origin, Point destination)
{
    std::list<NodePath*> nodes = pathfinder->find(origin.x, origin.y, destination.x, destination.y);
    Path* path = new Path(nodes);
    return path;
}

//TODO Check if the complete path is larger or equals to the unit movement
Path* Map::getUnitPath(Unit *unit, Point destination)
{
    Path* completePath = getPath(unit->getPosition(), destination);
    Path* unitPath = completePath->splice(unit->getMovement());
    
    return unitPath;
}

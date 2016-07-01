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
#include <list>

#include "Texture.h"
#include "Renderer.h"
#include "SDLTexture.h"
#include "Tile.h"
#include "Unit.h"
#include "Building.h"
#include "SpriteFactory.h"
#include "IMap.h"
#include "MapLayer.h"
#include <map>

static const int MAP_WIDTH = 15;
static const int MAP_HEIGHT = 10;

class Path;
class Pathfinder;
class Player;
class Map : public IMap {
public:
    typedef std::vector< std::vector<Tile*> > TileMap;
    Map();
    virtual ~Map();
    //Width and height in tiles
    void loadMap(Renderer* renderer, int width, int height);
    void drawMap(Renderer* renderer);
    
    Tile* matchEvent( const Point& position );
    
    //cast tile map position to absolute window coordinate position
    Point getAbsolutePosition( const Point& tilePosition );
    Point getAbsolutePosition(int x, int y);
    
    Tile getTile(int x, int y);
    Tile getTile(Point point);
    
    void updateUnitAvailableArea( const Unit& unit );
    void cleanUnitAvailableArea( const Unit& unit );
    
    void addBuilding(Building* building);
    Building* getBuilding(int id);
    Building* getBuilding(Point position);
    std::list<Building*> getBuildingsByOwnerId(int ownerId);
    int getNumBuildings(int ownerId);
    std::vector<Building*>& getBuildings();
    
    void loadBuildings(SpriteFactory* spriteFactory, Renderer* renderer,
                       Player* player, Player* opponent );
    
    //Check entities near the given unit(units, buildings...) and update his commands
    void checkNearEntities( const Unit& unit,
                            std::vector<UnitCommand>& commands);
    
    void restoreUnit( Unit& unit );
    void removeUnit( Unit& unit );
    
    int getNumRows();
    int getNumColumns();
    bool isValidPosition( const Point& position );
    
    void moveEntity( Unit& unit, const Point& destination );
    void loadInfoMap( std::list<Player *> &players );
    
    Unit* getEntity( const Point& reference ) const;
    
    void addEntity( Unit& unit );
    
private:
    TileMap matrix;
    
    std::vector<Building*> buildings;
    std::vector<Sprite*> sprites;
    
    MapLayer<Building*> structuresLayer;
    MapLayer<Unit*> entitiesLayer;
    
    std::map<int,Point> redArmyUnits;
    std::map<int,Point> blueArmyUnits;
    
    std::map<int,Point> entities;
 };

#endif /* defined(__ProjectWar__Map__) */

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
#include "InfoTile.h"
#include "Unit.h"
#include "Building.h"
#include "SpriteFactory.h"
#include "IMap.h"

static const int MAP_WIDTH = 15;
static const int MAP_HEIGHT = 10;


class Path;
class Pathfinder;
class Player;
class Map : public IMap {
public:
    typedef std::vector< std::vector<Tile*> > TileMap;
    typedef std::vector< std::vector<InfoTile*> > InfoMap;
    Map();
    virtual ~Map();
    //Width and height in tiles
    void loadMap(Renderer* renderer, int width, int height);
    void drawMap(Renderer* renderer);
    void drawInfoMap(Renderer* renderer);
    Tile* matchEvent(Point position);
    //cast tile map position to absolute window coordinate position
    Point getAbsolutePosition(Point tilePosition);
    Point getAbsolutePosition(int x, int y);
    
    Tile getTile(int x, int y);
    Tile getTile(Point point);
    
    void updateUnitAvailableArea(Unit* unit);
    void cleanUnitAvailableArea(Unit* unit);
    InfoTile& getInfoTile(Point position);
    
    void addBuilding(Building* building);
    Building* getBuilding(int id);
    Building* getBuilding(Point position);
    std::list<Building*> getBuildingsByOwnerId(int ownerId);
    int getNumBuildings(int ownerId);
    std::vector<Building*>& getBuildings();
    
    void loadBuildings(SpriteFactory* spriteFactory, Renderer* renderer,
                       Player* player, Player* opponent );
    
    //Initializes the values of the strategic info map
    void loadInfoMap( std::list<Player*> & players);
    InfoMap& getInfoMap();
    
    //Check entities near the given unit(units, buildings...) and update his commands
    void checkNearEntities(Unit* unit, std::list<UnitCommand>& commands);
    
    //Change unit position in the infomap, must be called before the unit position has been changed
    void moveUnit(Unit* unit, Point destination);
    void updateInfoTileBuilding(Unit* unit, Point destination);
    void updateInfoTileUnitCapturing(Unit* unit, Point destination);
    void updateInfoTile(Unit* unit, Point destination);
    
    void removeUnit(Unit* unit); //removes unit from the info map
    
    Path* getPath(Point origin, Point destination);
    //Return the path for the given unit, this means just the nodes that the unit can reach
    Path* getUnitPath(Unit* unit, Point destination);
    //Return the minium distance between two points in the map
    int getShortestDistance(Point origin, Point destination);
    
    void hideTile(Point position);
    
    int getNumRows();
    int getNumColumns();
    bool isValidPosition( Point position );
    std::pair<Point,Point>* getBoundingArea( Point position, int range );
    bool isOnBounds( Point position );
private:
    TileMap matrix;
    InfoMap infoMap;
    
    std::vector<Building*> buildings;
    std::list<Sprite*> sprites;
    Pathfinder* pathfinder;
 };

#endif /* defined(__ProjectWar__Map__) */

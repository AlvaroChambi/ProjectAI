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
#include "Camera.h"

static const int MAP_WIDTH = 15;
static const int MAP_HEIGHT = 10;


class Path;
class Pathfinder;
class Player;
class Map
{
public:
    typedef std::vector< std::vector<Tile*> > TileMap;
    typedef std::vector< std::vector<InfoTile*> > InfoMap;
    Map();
    virtual ~Map();
    //Width and height in tiles
    void loadMap(Renderer* renderer, int width, int height);
    void drawMap(Renderer* renderer, Camera* camera);
    void drawInfoMap(Renderer* renderer);
    Tile* matchEvent(Point position);
    int matchSpriteEvent(Point position);
    //cast tile map position to absolute window coordinate position
    Point getAbsolutePosition(Point tilePosition);
    Point getAbsolutePosition(int x, int y);
    
    Tile getTile(int x, int y);
    Tile getTile(Point point);
    
    bool isValidPosition(Point position);
    
    void updateUnitAvailableArea(Unit* unit);
    void cleanUnitAvailableArea(Unit* unit);
    InfoTile& getInfoTile(Point position);
    
    void addBuilding(Building* building);
    Building* getBuilding(int id);
    Building* getBuilding(Point position);
    std::list<Building*>& getBuildings();
    
    void loadBuildings(SpriteFactory* spriteFactory, Renderer* renderer);
    
    //Initializes the values of the strategic info map
    void loadInfoMap( std::list<Player*> & players);
    InfoMap& getInfoMap();
    
    //Check entities near the given unit(units, buildings...) and update his commands
    void checkNearEntities(Unit* unit, std::list<UnitCommand>& commands);
    
    //Change unit position in the infomap, must be called before the unit position has been changed
    void moveUnit(Unit* unit, Point destination);
    
    void removeUnit(Unit* unit); //removes unit from the info map
    
    Path* getPath(Point origin, Point destination);
    //Return the path for the given unit, this means just the nodes that the unit can reach
    Path* getUnitPath(Unit* unit, Point destination);
    
    void hideTile(Point position);
private:
    TileMap matrix;
    InfoMap infoMap;
    
    std::list<Building*> buildings;
    std::list<Sprite*> sprites;
    Pathfinder* pathfinder;
 };

#endif /* defined(__ProjectWar__Map__) */

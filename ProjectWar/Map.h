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
#include "InfoTile.h"
#include "List.h"
#include "Unit.h"
#include "Building.h"
#include "SpriteFactory.h"

static const int MAP_WIDTH = 15;
static const int MAP_HEIGHT = 10;
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
    void drawMap(Renderer* renderer);
    void drawInfoMap(Renderer* renderer);
    Tile* matchEvent(Point position);
    //cast tile map position to absolute window coordinate position
    Point getAbsolutePosition(Point tilePosition);
    Point getAbsolutePosition(int x, int y);
    
    Tile getTile(int x, int y);
    
    void updateUnitAvailableArea(Unit* unit);
    void cleanUnitAvailableArea(Unit* unit);
    
    void addBuilding(Building* building);
    Building* getBuilding(int id);
    Building* getBuilding(Point position);
    
    void loadBuildings(SpriteFactory* spriteFactory, Renderer* renderer);
    
    //Initializes the values of the strategic info map
    void loadInfoMap( List<Player*> & players);
    InfoMap& getInfoMap();
    
    //Check entities near the given unit(units, buildings...) and update his commands
    void checkNearEntities(Unit* unit, List<UnitCommand>& commands);
    
    //Change unit position in the infomap, must be called before the unit position has been changed
    void moveUnit(Unit* unit, Point destination);
    
    void removeUnit(Unit* unit); //removes unit from the info map
private:
    TileMap matrix;
    InfoMap infoMap;
    
    List<Building*> buildings;
    List<Sprite*> sprites;
 };

#endif /* defined(__ProjectWar__Map__) */

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
    
    void loadBuildings(SpriteFactory* spriteFactory, Renderer* renderer,
                       Player* player, Player* opponent );
    
    //Check entities near the given unit(units, buildings...) and update his commands
    void checkNearEntities( const Unit& unit,
                            std::vector<UnitCommand>& commands);
    
    int getNumRows();
    int getNumColumns();
    bool isValidPosition( const Point& position );
    void loadInfoMap( std::list<Player *> &players );
    
    void restoreUnit( Unit& unit );
    void removeUnit( Unit& unit );
    
    void moveEntity( Unit& unit, const Point& destination );
    Unit* getEntity( const Point& reference ) const;
    Unit* getEntity( int id ) const;
    void addEntity( Unit& unit );
    Point getEntityReference( int id ) const;
    
    void addStructure( Building& building );
    Point getStructureReference( int id );
    Building* getStructure( const Point& reference ) const;
    Building* getStructure( int id ) const;
    std::vector<Building*> getStructures() const;
private:
    TileMap matrix;
    std::vector<Sprite*> sprites;
    
    MapLayer<Building*> structuresLayer;
    MapLayer<Unit*> entitiesLayer;
    
    std::map<int,Point> entities;
    std::map<int,Point> structures;
 };

#endif /* defined(__ProjectWar__Map__) */

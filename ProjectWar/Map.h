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
#include "Unit.h"
#include "Building.h"
#include "SpriteFactory.h"
#include "MapLayer.h"
#include "MapContext.h"

#include <map>

static const int MAP_WIDTH = 15;
static const int MAP_HEIGHT = 10;

class Player;
class Map : public MapContext {
public:
    typedef std::vector< std::vector<Tile*> > TileMap;
    Map( const Player& player, const Player& opponent );
    ~Map();
    //Width and height in tiles
    void loadMap( Renderer* renderer, int width, int height );
    void drawMap( Renderer* renderer );
    void loadInfoMap( std::list<Player *> &players );
    
    Tile* matchEvent( const Point& position );
    
    //cast tile map position to absolute window coordinate position
    Point getAbsolutePosition( const Point& tilePosition );
    Point getAbsolutePosition( int x, int y );
    
    void updateUnitAvailableArea( const Unit& unit );
    void cleanUnitAvailableArea( const Unit& unit );
    
    void loadBuildings( SpriteFactory* spriteFactory, Renderer* renderer,
                        Player* player, Player* opponent );
    
    void checkNearEntities( const Unit& unit,
                            std::vector<UnitCommand>& commands);
    
    //override
    int getNumRows() const;
    int getNumColumns() const;
    
    bool isValidPosition( const Point& position ) const;
    
    Tile getTile( const Point& point ) const;
    
    void addEntity( Unit& unit );
    Unit* getEntity( const Point& reference ) const;
    Unit* getEntity( int id ) const;
    Point getEntityReference( int id ) const;
    
    void moveEntity( Unit& unit, const Point& destination );
    
    void restoreUnit( Unit& unit );
    void removeUnit( Unit& unit );
    
    void addStructure( Building& building );
    Building* getStructure( const Point& reference ) const;
    Building* getStructure( int id ) const;
    std::vector<Building*> getStructures() const;
    
    const Player& getPlayer() const;
    const Player& getOpponent() const;
private:
    TileMap matrix;
    std::vector<Sprite*> sprites;
    
    MapLayer<Building*> structuresLayer;
    MapLayer<Unit*> entitiesLayer;
    
    std::map<int,Point> entities;
    std::map<int,Point> structures;
    
    const Player& player;
    const Player& opponent;
 };

#endif /* defined(__ProjectWar__Map__) */

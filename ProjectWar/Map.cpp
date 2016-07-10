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
#include "GameException.h"
#include "AreaIterator.h"
#include "UnitFilter.h"

Map::Map() {
    entitiesLayer.resize( MAP_WIDTH , MAP_HEIGHT );
    structuresLayer.resize( MAP_WIDTH, MAP_HEIGHT );
    
    matrix.resize(MAP_WIDTH);
    for(int i = 0; i < MAP_WIDTH; i++){
        matrix.at(i).resize(MAP_HEIGHT, 0);
    }
}

Map::~Map() {

}

int Map::getNumColumns() const {
    return MAP_WIDTH;
}

int Map::getNumRows() const {
    return MAP_HEIGHT;
}

//Using static map width and height for now
void Map::loadMap( Renderer* renderer, int tileWidth, int tileHeight ) {
    for(int i = 0; i < MAP_WIDTH ; i++){
        int posX = i * tileWidth;
        for(int j = 0; j < MAP_HEIGHT ; j++){
            int posY = j * tileHeight;
            //use static color !Change this¡
            Color color = Color(0,153,0);
            Texture * texture = renderer->loadShape( RECTANGLE, color,
                                                     tileWidth, tileHeight);
            texture->setPosition(posX, posY);
            Tile* tile = new Tile(texture);
            tile->position.x = i;
            tile->position.y = j;
            matrix[i][j] = tile;
        }
    }
}

void Map::loadBuildings(SpriteFactory* spriteFactory, Renderer* renderer,
                        Player* player, Player* opponent ) {
    Building* building = new Building();
    Sprite* buildingSprite = spriteFactory->createSprite(BUILDING);
    building->setCapturePoints(20);
    buildingSprite->setModel(building);
    buildingSprite->setTexture(renderer->loadSprite("building.png", 32, 32));
    buildingSprite->resize(40, 40);
    building->setPosition(getTile( Point(2, 2) ));
    buildingSprite->setRenderFrame(Point(3,0));
    building->setOwnerID(0);
    building->setCaptureValue(20);
    this->addStructure( *building );
    
    Building* building2 = new Building();
    Sprite* buildingSprite2 = spriteFactory->createSprite(BUILDING);
    building2->setCapturePoints(20);
    buildingSprite2->setModel(building2);
    buildingSprite2->setTexture(renderer->loadSprite("building.png", 32, 32));
    buildingSprite2->resize(40, 40);
    buildingSprite2->setRenderFrame(Point(3,0));
    building2->setOwnerID(1);
    building2->setCaptureValue(20);
    building2->setPosition(getTile(Point(12,6)));
    this->addStructure( *building2 );
    
    player->setHeadquarter( building->getId() );
    opponent->setHeadquarter( building2->getId() );
    
    sprites.push_back(buildingSprite);
    sprites.push_back(buildingSprite2);
}

void Map::cleanUnitAvailableArea( const Unit& unit ) {
    AreaIterator areaIterator;
    areaIterator.buildArea( unit.getPosition(), unit.getMovement(),
                           MAP_WIDTH, MAP_HEIGHT );
    
    UnitMovementFilter filter( areaIterator, this, unit );
    while ( filter.hasNext() ) {
        Point destination = filter.next();
        matrix[destination.x][destination.y]->getTexture()->setVisible(true);
    }
}

void Map::updateUnitAvailableArea( const Unit& unit ) {
    AreaIterator areaIterator;
    areaIterator.buildArea( unit.getPosition(), unit.getMovement(),
                           MAP_WIDTH, MAP_HEIGHT );
    
    UnitMovementFilter filter( areaIterator, this, unit );
    while ( filter.hasNext() ) {
        Point destination = filter.next();
        matrix[destination.x][destination.y]->getTexture()->setVisible(false);
    }
}

void Map::drawMap(Renderer* renderer) {
    for(int i = 0; i < MAP_WIDTH; i++){
        for(int j = 0; j < MAP_HEIGHT; j++){
            if(matrix[i][j]->getTexture()->isVisible()){
                renderer->drawTexture(matrix[i][j]->getTexture());
            }
        }
        
    }
    
    for (Sprite* sprite : sprites) {
        sprite->render(renderer);
    }
}

Tile* Map::matchEvent( const Point& position ) {
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

Point Map::getAbsolutePosition( const Point& tilePosition ) {
    Point point;
    if (tilePosition.x < MAP_WIDTH && tilePosition.y < MAP_HEIGHT) {
        point = matrix[tilePosition.x][tilePosition.y]->getTexture()->getPosition();
    }
    return point;
}

Point Map::getAbsolutePosition( int x, int y ) {
    Point point;
    point.x = x;
    point.y = y;
    return getAbsolutePosition( point );
}

Tile Map::getTile( const Point& point ) const {
    return *matrix[point.x][point.y];
}

bool Map::isValidPosition( const Point& position ) const {
    return entitiesLayer.get( position ) == nullptr;
}

void Map::loadInfoMap( std::list<Player *> &players ) {
    for (Player* player : players) {
        std::vector<Unit*> units = player->getUnits();
        for( Unit* unit : units ) {
            entitiesLayer.set( unit , unit->getPosition() );
        }
    }
}

void Map::checkNearEntities( const Unit& unit,
                             std::vector<UnitCommand>& commands ) {
    AreaIterator areaIterator;
    areaIterator.buildArea( unit.getPosition(), unit.getAttackRange(),
                           MAP_WIDTH, MAP_HEIGHT );
    
    Building* structure = structuresLayer.get( unit.getPosition() );
    if( structure != nullptr && !structure->isCaptured( unit.getOwnerID() ) ) {
        //structure available to capture
        commands.push_back( CAPTURE );
    }
    
    //Decorate with unit movement filter -> crash!
    while ( areaIterator.hasNext() ) {
        Point destination = areaIterator.next();
        Unit* entity = entitiesLayer.get( destination );
        if( unit.getPosition().onRange( destination , unit.getAttackRange() )
            && entity != nullptr && entity->getOwnerID() != unit.getOwnerID() ) {
            commands.push_back( ATTACK );
            return;
        }
    }
}

// An exception will be raised if the unit is already added
// or his position is already occupied
void Map::addEntity( Unit& unit ) {
    if( entities.find( unit.getId() ) == entities.end()
        && entitiesLayer.get( unit.getPosition() ) == nullptr ) {
        
        entitiesLayer.set( &unit, unit.getPosition() );
        entities[unit.getId()] = unit.getPosition();
    } else {
        throw IllegalStateException("");
    }
}

void Map::moveEntity( Unit& unit, const Point &destination ) {
    entitiesLayer.move( unit.getPosition(), destination );
    entities[unit.getId()] = destination;
}

void Map::restoreUnit( Unit& unit ) {
    entitiesLayer.set( &unit, unit.getPosition() );
    entities[unit.getId()].invalidated = false;
}

void Map::removeUnit( Unit& unit ) {
    entitiesLayer.set( nullptr, unit.getPosition() );
    entities[unit.getId()].invalidated = true;
}

Unit* Map::getEntity( const Point &reference ) const {
    if( !reference.invalidated ) {
        return entitiesLayer.get( reference );
    }
    return nullptr;
}

Unit* Map::getEntity( int id ) const {
    return getEntity( entities.at( id ) );
}

Point Map::getEntityReference( int id ) const {
    return entities.at( id );
}

Building* Map::getStructure( const Point &reference ) const {
    if( !reference.invalidated ) {
        return structuresLayer.get( reference );
    }
    return nullptr;
}

Building* Map::getStructure( int id ) const {
    return getStructure( structures.at( id ) );
}

// An exception will be raised if the structure is already added
// or his position is already occupied
void Map::addStructure( Building &building ) {
    if( structures.find( building.getId() ) == structures.end()
       && structuresLayer.get( building.getPosition() ) == nullptr ) {
        
        structuresLayer.set( &building, building.getPosition() );
        structures[building.getId()] = building.getPosition();
    } else {
        throw IllegalStateException("");
    }
}

std::vector<Building*> Map::getStructures() const {
    std::vector<Building*> result;
    for ( const auto &pair : structures ) {
        result.push_back( getStructure( pair.second ) );
    }
    return result;
}
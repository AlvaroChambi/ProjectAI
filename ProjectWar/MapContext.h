//
//  MapContext.h
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 10/7/16.
//  Copyright © 2016 Alvaro Chambi Campos. All rights reserved.
//

#ifndef MapContext_h
#define MapContext_h

#include "Unit.h"

class MapContext {
public:
    virtual int getNumRows() const = 0;
    virtual int getNumColumns() const = 0;
    
    virtual bool isValidPosition( const Point& position ) const = 0;
    
    virtual Tile getTile( const Point& position) const= 0;
    
    virtual void addEntity( Unit& unit ) = 0;
    virtual Unit* getEntity( const Point& reference ) const = 0;
    virtual Unit* getEntity( int id ) const = 0;
    virtual Point getEntityReference( int id ) const = 0;
    
    virtual void moveEntity( Unit& unit, const Point& destination ) = 0;
    
    virtual void restoreUnit( Unit& unit ) = 0;
    virtual void removeUnit( Unit& unit ) = 0;
    
    virtual void addStructure( Building& building ) = 0;
    virtual Building* getStructure( const Point& reference ) const = 0;
    virtual Building* getStructure( int id ) const = 0;
    virtual std::vector<Building*> getStructures() const = 0;
    
    virtual const Player& getPlayer() const = 0;
    virtual const Player& getOpponent() const = 0;
    
    virtual const Player* getPlayer( const int id ) const = 0;
};

#endif /* MapContext_h */

//
//  Building.h
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 11/4/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#ifndef __ProjectWar__Building__
#define __ProjectWar__Building__

#include <stdio.h>
#include "Model.h"
#include "Tile.h"

class Building : public Model
{
public:
    Building();
    Building( const Building& building );
    Tile getTile() const;
    Point getPosition() const;
    void setPosition( const Tile& position );
    
    void setCapturePoints( int value );
    int getCapturePoints() const;
    
    void setCaptureValue(int value);
    int getCaptureValue() const;
    
    void setOwnerID(int id);
    int getOwnerID() const;
    
    bool isCaptured( int playerID ) const;
private:
    int ownerID;
    Tile tile;
    int capturePoints;
    int captureValue;
};

#endif /* defined(__ProjectWar__Building__) */

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
    virtual ~Building();
    Tile getTile();
    Point getPosition();
    void setPosition(Tile position);
    
    void setCapturePoints(int value);
    int getCapturePoints();
    
    void setCaptureValue(int value);
    int getCaptureValue();
    
    void setOwnerID(int id);
    int getOwnerID();
    
    bool isCaptured(int playerID);
private:
    int ownerID;
    Tile tile;
    int capturePoints;
    int captureValue;
};

#endif /* defined(__ProjectWar__Building__) */

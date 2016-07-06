//
//  MovesBuilder.h
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 06/07/16.
//  Copyright (c) 2016 Alvaro Chambi Campos. All rights reserved.
//

#ifndef ProjectWar_MovesBuilder_h
#define ProjectWar_MovesBuilder_h

#include "Map.h"
#include "Action.h"

#include <vector>

class MovesBuilder {
public:
    MovesBuilder( const Map& map );
    
    std::vector<Action*> getActions();
    int buildActions( int playerID );
    void buildActions( int playerID, int numActions );
    
    void buildUnitActions( int unitID, int playerID ,int numActions );
    
    void resolveActions( const Unit& unit, int playerID,
                         const Point& destination,
                         std::vector<Action*>& actions );
    void appendAttackActions( const Unit& unit, const Unit& target,
                              std::vector<Action*>& actions );
    void appendCaptureAction( const Unit& unit, const Building& structure,
                              std::vector<Action*>& actions );
    void appendMoveAction( const Unit& unit,
                           std::vector<Action*>& actions );
private:
    const Map& map;
    std::vector<Action*> actions;
};

#endif

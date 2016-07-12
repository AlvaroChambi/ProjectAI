//
//  ActionsProvider.h
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 10/7/16.
//  Copyright © 2016 Alvaro Chambi Campos. All rights reserved.
//

#ifndef ActionsProvider_h
#define ActionsProvider_h

#include "MapContext.h"
#include "ActionBuilder.h"

class ActionsProvider {
public:
    ActionsProvider( MapContext& context );
    
    std::vector<Option*> generateMovements( int playerID,
                                            int numActions ) const;

    void buildActions( int playerID, int numActions );
    
    std::vector<Action*>& buildUnitActions( int unitID,
                                     int playerID ,int numActions );
    ActionBuilder& createActionBuilder( const Unit& unit, int playerID,
                                        const Point& destination );
    
    
    void appendUnitActions( std::vector<Action*> actions, int numActions );
    
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
    MapContext& mapContext;
    std::vector<Action*> actions;
};

#endif /* ActionsProvider_h */

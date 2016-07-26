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
#include "ActionsBuilder.h"
#include "Movement.h"

class ActionsProvider {
public:
    ActionsProvider( MapContext& context );
    
    std::vector<Option*> generateMovements( int playerID,
                                            int numActions ) const;

    void buildActions( int playerID, int numActions );
    
    std::vector<Action*>& buildUnitActions( const int unitID );
    
    TargetTile getTargetTileForPosition( const int unitID,
                                         const Point& position );
    std::vector<Movement*>& mapVariations(
                        const int numUnits,
                        std::vector<std::vector<int>>& variations,
                        std::vector<Action*>& actions );
private:
    MapContext& mapContext;
    ActionsBuilder actionsBuilder;
    std::vector<Action*> actions;
};

#endif /* ActionsProvider_h */

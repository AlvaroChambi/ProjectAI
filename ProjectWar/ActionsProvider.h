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

class ActionsProvider {
public:
    ActionsProvider( MapContext& context );
    
    std::vector<Option*> generateMovements( int playerID,
                                            int numActions ) const;

    void buildActions( int playerID, int numActions );
    
    std::vector<Action*>& buildUnitActions( const int unitID,
                                    ActionsBuilder& actionsBuilder );
    
    TargetTile getTargetTileForPosition( const int unitID,
                                         const Point& position );
private:
    MapContext& mapContext;
    std::vector<Action*> actions;
};

#endif /* ActionsProvider_h */

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
#include "Evaluator.h"
#include "ActionsBuilder.h"
#include "Movement.h"
#include "MovementsList.h"

class ActionsProvider {
public:
    ActionsProvider( MapContext& context );
    
    MovementsList& generateMovements( int playerID,
                                            int numActions ) const;
    
    std::vector<Action*>& buildUnitActions( const int unitID ) const;
    
    void sortActions( std::vector<Action*>& actions,
                      const Evaluator& evaluator ) const;
    
    TargetTile getTargetTileForPosition( const int unitID,
                                         const Point& position ) const;
    MovementsList& mapVariations(
                        const int numActions,
                        std::vector<std::vector<int>>& variations,
                        std::vector<Action*>& actions ) const;
    
    std::vector<std::vector<int>>& generateVariations(
                                        int numActions, int numUnits ) const;
private:
    void generateVariations( std::vector<std::vector<int>> *sequence,
                            int numElements, std::vector<int> variation,
                            int count ) const;
    
    MapContext& mapContext;
    ActionsBuilder actionsBuilder;
};

#endif /* ActionsProvider_h */

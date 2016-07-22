//
//  AttackActionsBuilder.h
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 12/7/16.
//  Copyright © 2016 Alvaro Chambi Campos. All rights reserved.
//

#ifndef ActionsBuilder_h
#define ActionsBuilder_h

#include "Action.h"
#include "Point.h"

enum TargetTile {
    TARGET_NOT_AVAILABLE,
    TARGET_ENTITY,
    TARGET_STRUCTURE,
    TARGET_POSITION,
};

class ActionsBuilder {
public:
    void createAppendAttackActions( MapContext& context,
                            const int unitID, const Point& position,
                            std::vector<Action*>& vector ) const;
    
    void createAppendMoveAction( MapContext& context,
                                const int unitID, const Point& position,
                                 std::vector<Action*>& vector ) const;
    void createAppendCaptureAction( MapContext& context,
                                   const int unitID, const Point& position,
                                   std::vector<Action*>& vector  ) const;
    
    void appendActions( const TargetTile& targetTile,
                        MapContext& context,
                        const int unitID, const Point& position,
                        std::vector<Action*>& vector ) const;
};

#endif /* AttackActionsBuilder_h */

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
    TARGET_ENTITY,
    TARGET_STRUCTURE,
    TARGET_POSITION,
};

class ActionsBuilder {
public:
    ActionsBuilder( const int unitID, const Point& position );
    
    void createAppendAttackActions( MapContext& context,
                              std::vector<Action*>& vector ) const;
    
    void createAppendMoveAction( MapContext& context,
                                 std::vector<Action*>& vector ) const;
    void createAppendCaptureAction( MapContext& context,
                                   std::vector<Action*>& vector  ) const;
    
    void appendActions( const TargetTile& targetTile,
                        MapContext& context,
                        std::vector<Action*>& vector ) const;
    
    //targetEntityTile
    //targetStructureTile
    //targetPositionTile
private:
    const int unitID;
    const Point& position;
};

#endif /* AttackActionsBuilder_h */

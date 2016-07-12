//
//  ActionBuilder.h
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 11/7/16.
//  Copyright © 2016 Alvaro Chambi Campos. All rights reserved.
//

#ifndef ActionBuilder_h
#define ActionBuilder_h

#include "Action.h"

class Point;

class ActionBuilder {
public:
    virtual Action& createAction( MapContext& mapContext ) const = 0;
};

class MoveActionBuilder : public ActionBuilder {
public:
    MoveActionBuilder( const int unitID, const Point& destination );
    Action& createAction( MapContext& context ) const;
    
private:
    const int unitID;
    const Point& destination;
};

class CaptureActionBuilder : public ActionBuilder {
public:
    CaptureActionBuilder( const int unitID, const Point& destination );
    Action& createAction( MapContext& context ) const;
    
private:
    const int unitID;
    const Point& destination;
};

class AttackActionBuilder : public ActionBuilder {
public:
    AttackActionBuilder( const int unitID, const int targetID,
                         const Point& destination );
    Action& createAction( MapContext& context ) const;
    
private:
    const int unitID;
    const int targetID;
    const Point& destination;
};

#endif /* ActionBuilder_h */

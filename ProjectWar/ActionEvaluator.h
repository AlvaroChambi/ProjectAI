//
//  ActionEvaluator.h
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 28/07/16.
//  Copyright (c) 2016 Alvaro Chambi Campos. All rights reserved.
//

#ifndef ProjectWar_ActionEvaluator_h
#define ProjectWar_ActionEvaluator_h

#include "Evaluator.h"

class ActionEvaluator : public Evaluator {
public:
    float getEvaluation( const Action& action,
                       const MapContext& context ) const;
    float evaluateValues( const float headquarterInfluence,
                          const float enemyHeadquarterInfluence,
                          const float alliesInfluence,
                          const float opponentsInfluence ) const;
    float getHeadquarterInfluence( const Point& position,
                                   const MapContext& context ) const;
    float getOpponentHeadquarterInfluence( const Point& position,
                                           const MapContext& context ) const;
    float getAlliesInfluence( const Point& position,
                              const MapContext& context ) const;
    float getOpponentsInfluence( const Point& position,
                                 const MapContext& context ) const;
};

#endif

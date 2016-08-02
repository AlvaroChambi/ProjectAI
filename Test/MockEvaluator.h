//
//  MockEvaluator.h
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 02/08/16.
//  Copyright (c) 2016 Alvaro Chambi Campos. All rights reserved.
//

#ifndef ProjectWar_MockEvaluator_h
#define ProjectWar_MockEvaluator_h

#include "gmock/gmock.h"
#include "Evaluator.h"

class MockEvaluator : public  Evaluator {
public:
    MOCK_CONST_METHOD2( getEvaluation, float( const Action& action,
                                              const MapContext& context ) );
};

#endif

//
//  Evaluator.h
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 28/07/16.
//  Copyright (c) 2016 Alvaro Chambi Campos. All rights reserved.
//

#ifndef ProjectWar_Evaluator_h
#define ProjectWar_Evaluator_h

#include "MapContext.h"

class Evaluator {
public:
    virtual int getEvaluation( const Action& action,
                               const MapContext& context );
};

#endif

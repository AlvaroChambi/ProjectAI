//
//  Command.h
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 21/3/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#ifndef __ProjectWar__Command__
#define __ProjectWar__Command__

#include <stdio.h>
#include <iostream>
#include "Option.h"

class Command : public Option {
public:
    virtual ~Command(){}
    virtual void execute() = 0;
    virtual void cancel() = 0;
};

#endif /* defined(__ProjectWar__Command__) */

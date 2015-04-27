//
//  Option.h
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 25/4/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#ifndef ProjectWar_Option_h
#define ProjectWar_Option_h

class Option
{
public:
    Option(){}
    virtual ~Option(){}
    int value;
    virtual void execute() = 0;
    virtual void cancel() = 0;
};

#endif

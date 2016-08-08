//
//  Option.h
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 25/4/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#ifndef ProjectWar_Option_h
#define ProjectWar_Option_h

class MapContext;
class Option
{
public:
    virtual void execute( MapContext& context ) = 0;
    virtual void cancel() = 0;
};

#endif

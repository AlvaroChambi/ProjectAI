//
//  Color.h
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 13/3/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#ifndef __ProjectWar__Color__
#define __ProjectWar__Color__

#include <stdio.h>

class Color
{
public:
    Color(int r, int g, int b);
    virtual ~Color();
    int r;
    int g;
    int b;
};

#endif /* defined(__ProjectWar__Color__) */

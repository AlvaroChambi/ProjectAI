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
    Color(int r, int g, int b) : a(0)
    {
        this->r = r;
        this->g = g;
        this->b = b;
    }
    
    ~Color()
    {
        
    }
    int r;
    int g;
    int b;
    int a;
};

#endif /* defined(__ProjectWar__Color__) */

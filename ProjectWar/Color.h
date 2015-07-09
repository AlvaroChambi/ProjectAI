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



//TODO make this an enum...
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
    /*
    */
};

namespace Colors {
    const Color RED = Color(255,0,0);
    const Color GREEN = Color(0,153,0);
    const Color BLUE = Color(0,0,255);
    const Color YELLOW = Color(255,255,0);
    const Color CIAN = Color(0,255,255);
}


#endif /* defined(__ProjectWar__Color__) */

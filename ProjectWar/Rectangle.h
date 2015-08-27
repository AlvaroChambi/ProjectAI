//
//  Rectangle.h
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 15/8/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#ifndef __ProjectWar__Rectangle__
#define __ProjectWar__Rectangle__

#include <stdio.h>

class Rectangle
{
public:
    Rectangle();
    ~Rectangle();
    
    int width;
    int height;
    int x;
    int y;
    bool filled;
};

#endif /* defined(__ProjectWar__Rectangle__) */

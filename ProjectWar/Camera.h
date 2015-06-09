//
//  Camera.h
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 8/6/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#ifndef __ProjectWar__Camera__
#define __ProjectWar__Camera__

#include <stdio.h>
#include "Point.h"

class Camera
{
public:
    Camera();
    Camera(Point position, int width, int height);
    ~Camera();
    Point position;
    int width;
    int height;
};

#endif /* defined(__ProjectWar__Camera__) */

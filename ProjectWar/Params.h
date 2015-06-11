//
//  Params.h
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 24/3/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#ifndef ProjectWar_Params_h
#define ProjectWar_Params_h

static const int FILL = 0;
static const int WRAP = 1;

enum Gravity{
    CENTER,
    UP,
    DOWN,
    CENTER_DOWN,
};

class Params
{
public:
    Params() : width(FILL), height(FILL), gravity(CENTER)
    {}
    Params(int width, int height, Gravity gravity) : width(width), height(height), gravity(gravity)
    {}
    virtual ~Params(){}
    int width;
    int height;
    Gravity gravity;
};

#endif

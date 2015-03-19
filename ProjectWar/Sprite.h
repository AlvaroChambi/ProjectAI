//
//  Sprite.h
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 17/3/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#ifndef __ProjectWar__Sprite__
#define __ProjectWar__Sprite__

#include <stdio.h>

#include "View.h"

class Sprite : public View
{
public:
    Sprite();
    virtual ~Sprite();
    void setID( int id );
    int getID();
private:
    int id;
};

#endif /* defined(__ProjectWar__Sprite__) */
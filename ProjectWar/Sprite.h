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
    void setTexture(Texture* texture);
    virtual void updateFrame();
    void startAnimation();
    void resize(int width, int height);
    int getWidth();
    int getHeight();
private:
    int id;
    int frame;
    bool animated;
    int width;
    int height;
};

#endif /* defined(__ProjectWar__Sprite__) */

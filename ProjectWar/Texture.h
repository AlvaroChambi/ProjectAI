//
//  Texture.h
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 10/3/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#ifndef __ProjectWar__Texture__
#define __ProjectWar__Texture__

#include <stdio.h>
#include "Point.h"

class Texture
{
public:
    Texture();
    virtual ~Texture();
    virtual void* getTexture() = 0;
    virtual void setTexture(void* texture) = 0;
    void setPosition(int x, int y);
    Point getPosition();
    void setPosition( Point position );
    void setWidth( int width );
    int getWidth();
    void setZOrder( int zOrder );
    int getZOrder();
    void setHeight( int height );
    int getHeight();
    Point getSourceRect();
    void setSourceRect(Point position);
    int getFrameWidth();
    void setFrameWidth(int width);
    int getFrameHeight();
    void setFrameHeight(int height);
    
    bool matchPosition(Point position);
private:
    //used to handle animated sprites
    Point sourceRect;
    int frameWidth;
    int frameHeight;
    
    Point position;
    int width;
    int height;
    int zOrder;
};

#endif /* defined(__ProjectWar__Texture__) */

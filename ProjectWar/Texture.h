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
    void setZorder(int z);
    Point getPosition();
    void setPosition( Point position );
    void setWidth( int width );
    int getWidth();
    void setHeight( int height );
    int getHeight();
    Point getFramePosition();
    void setFramePosition(Point position);
    int getFrameWidth();
    void setFrameWidth(int width);
    int getFrameHeight();
    void setFrameHeight(int height);
    void setVisible(bool visibility);
    bool isVisible();
    
    bool matchPosition(Point position);
private:
    Point framePosition;  //Position of the frame to render relative to the texture
    int frameWidth;       //Dimension of the zone of the texture to render(whole texture if it's not animated)
    int frameHeight;
    
    bool visible;
    Point position;       //position relative to the screen
    int width;            //Dimensions of the whole texture(never used to render, always render with the frame dimensions)
    int height;
};

#endif /* defined(__ProjectWar__Texture__) */

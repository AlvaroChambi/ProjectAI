//
//  Sprite.h
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 8/4/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#ifndef __ProjectWar__Sprite__
#define __ProjectWar__Sprite__

#include <stdio.h>
#include "Renderer.h"

#include "Observer.h"
#include "Texture.h"
#include "Model.h"

class Sprite : public Observer
{
public:
    Sprite();
    virtual ~Sprite();
    virtual void updateFrame();
    virtual void render(Renderer* renderer);
    virtual void setModel(Model* model) = 0;
    void setID( int id );
    int getID();
    
    void setRenderFrame(Point position);
    
    void setTexture(Texture* texture);
    Texture* getTexture();
    void updateAnimated(bool animated);
    void resize(int width, int height);
    bool matchPosition(Point position);
    int getWidth();
    int getHeight();
private:
    Texture* texture;
    int id;
    int frame;
    bool animated;
    int width;
    int height;
};

#endif /* defined(__ProjectWar__Sprite__) */

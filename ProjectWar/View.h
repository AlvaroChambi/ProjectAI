//
//  View.h
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 13/3/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#ifndef __ProjectWar__View__
#define __ProjectWar__View__

#include <stdio.h>
#include <iostream>
#include "Model.h"
#include "Texture.h"
#include "Observer.h"

class View : public Observer
{
public:
    View();
    virtual ~View();
    virtual void setModel(Model* model);
    void setTexture(Texture* texture);
    Texture* getTexture();
private:
    Texture* texture;
};

#endif /* defined(__ProjectWar__View__) */

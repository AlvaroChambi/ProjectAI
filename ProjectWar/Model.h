//
//  Model.h
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 13/3/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#ifndef __ProjectWar__Model__
#define __ProjectWar__Model__

#include <stdio.h>
#include "Observable.h"

class Model : public Observable
{
public:
    Model();
    virtual ~Model();
    int getId();
    void setid(int id);
private:
    int id;
};

#endif /* defined(__ProjectWar__Model__) */

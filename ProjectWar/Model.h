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
#include <iostream>
#include "Observable.h"

class Model : public Observable
{
public:
    Model();
    virtual ~Model();
    int getId() const;
    void setid( int id );
    void setResource( std::string resource );
    std::string getResource() const;
private:
    int id;
    std::string resource ;
};

#endif /* defined(__ProjectWar__Model__) */

//
//  Army.h
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 9/7/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#ifndef ProjectWar_Army_h
#define ProjectWar_Army_h

#include <string>

class Army
{
public:
    const std::string ARMY_RED = "red";
    const std::string ARMY_BLUE = "blue";
    
    Army(std::string name) : name(name)
    {}
    ~Army(){}
    
    std::string name;
};

#endif

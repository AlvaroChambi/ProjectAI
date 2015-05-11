//
//  Path.h
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 2/5/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#ifndef __ProjectWar__Path__
#define __ProjectWar__Path__

#include <stdio.h>
#include <list>
#include "NodePath.h"

class Path
{
public:
    Path();
    Path(std::list<NodePath*> pathNodes);
    ~Path();
    
    void printPath();
    NodePath* getNode(int position);
    NodePath* getLastNode();
    Path* splice(int numNodes);
    int size();
private:
    std::list<NodePath*> pathNodes;
};

#endif /* defined(__ProjectWar__Path__) */

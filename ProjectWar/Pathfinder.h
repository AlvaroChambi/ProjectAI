//
//  Pathfinder.h
//  ProjectWar
//
//  Created by Pablo Luis Gutierrez on 22/04/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#ifndef __ProjectWar__Pathfinder__
#define __ProjectWar__Pathfinder__

#include <stdio.h>
#include <vector>
#include <list>
#include <set>
#include "NodePath.h"


class Pathfinder
{

public:
    
    Pathfinder();
    Pathfinder(Map *map);
    std::list<NodePath*> find(int sourceX, int sourceY, int targetX, int targetY);
    void setSource(int x, int y);
    void setTarget(int x, int y);
    void finish();
    void consider(NodePath* parent, int x, int y);
    bool compare_points(NodePath *start);
    void printList(std::list<NodePath*> NodePaths);
    void printPath(Path* path);
private:

    std::list<NodePath*> NodePaths;
    std::list<NodePath*> openSet;
    std::list<NodePath*> closedSet;

    NodePath *source;
    NodePath *target;
    
    Map *map;
    
    bool found;

};


#endif /* defined(__ProjectWar__Pathfinder__) */

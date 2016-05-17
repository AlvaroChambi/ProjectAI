//
//  Path.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 2/5/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#include "Path.h"

Path::Path()
{

}

Path::Path(std::list<NodePath*> nodes) : pathNodes(nodes)
{

}

Path::~Path()
{

}

Path* Path::splice(int numNodes)
{
    Path* result = nullptr;
    std::list<NodePath*> nodes;
    std::list<NodePath*>::iterator iterator = pathNodes.begin();
    std::advance(iterator, numNodes);
    
    nodes.splice(nodes.begin(),pathNodes, pathNodes.begin(), iterator);
    
    result = new Path(nodes);
    return result;
}

NodePath* Path::getNode(int position)
{
    std::list<NodePath*>::iterator iterator = pathNodes.begin();
    std::advance(iterator, position);
    
    return *iterator;
}

NodePath* Path::getLastNode()
{
    return pathNodes.back();
}

void Path::printPath()
{
    for (NodePath* node :  pathNodes) {
        std::cout << node->getPoint() << " \n";
    }
}

int Path::size()
{
    return (int)pathNodes.size();
}
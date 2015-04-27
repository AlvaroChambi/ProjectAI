//
//  Pathfinder.cpp
//  ProjectWar
//
//  Created by Pablo Luis Gutierrez on 22/04/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#include "Pathfinder.h"
#include <set>

Pathfinder::Pathfinder()
{
    source = new NodePath();
    target = new NodePath();
}

Pathfinder::Pathfinder(Map* map)
{
    source = new NodePath();
    target = new NodePath();
    this->map = map;
}

bool sort_by_f (const NodePath* first, const NodePath* second)
{
    if( first->getF()<second->getF())
        return true;
    else
        return false;
}

bool findElement(std::list<NodePath*> list, NodePath* node)
{
    std::list<NodePath*>::iterator it;
    bool result = false;
    it = list.begin();
    while (!result && it!=list.end()) {
        NodePath* nodeit = *it;
        if(node->getPoint() == nodeit->getPoint()){
            result = true;
        }
        else{
            result = false;
        }
        it++;
    }
    
    return result;
}


void Pathfinder::setSource(int x, int y)
{
    source->setPoint(Point(x,y));
    openSet.push_back(source);
}

void Pathfinder::setTarget(int x, int y)
{
    target->setPoint(Point(x,y));
}

std::list<NodePath*> Pathfinder::find(int sourceX, int sourceY, int targetX, int targetY)
{
    found = false;
    openSet.clear();
    closedSet.clear();
    
    setSource(sourceX, sourceY);
    setTarget(targetX, targetY);
    
    while(!found && !openSet.empty()) {
        NodePath *cur = new NodePath();
        cur = *(openSet.begin());
        openSet.remove(cur);
        closedSet.push_back(cur);
        
        if(cur->getPoint() == target->getPoint()) {
            finish();
        }
        //consider(cur, -1, -1);
        consider(cur, +0, -1);
        //consider(cur, +1, -1);
        consider(cur, -1, +0);
        consider(cur, +1, +0);
        //consider(cur, -1, +1);
        consider(cur, +0, +1);
        //consider(cur, +1, +1);
    }
    return NodePaths;
}

bool Pathfinder::compare_points(NodePath *start)
{
    if(start->getPoint()==source->getPoint()){
        return true;
    }
    else
        return false;
}

void Pathfinder::finish()
{
    found = true;
    NodePath* cur = target;
    NodePaths.clear();
    while(!compare_points(cur)) {
        NodePaths.push_back(cur);
        cur = cur->getParent();
    }
    NodePaths.push_back(source);
    NodePaths.reverse();
}

void Pathfinder::printList(std::list<NodePath *> nodePaths)
{
    for (NodePath* node :  nodePaths) {
        std::cout << "x: " + std::to_string(node->getPoint().x)
        + "y: " + std::to_string(node->getPoint().y);
    }
}

void Pathfinder::consider(NodePath* parent, int x, int y)
{
    NodePath* cur = new NodePath();
    cur->setPoint(Point(parent->getPoint().x + x, parent->getPoint().y + y));
    if(cur->accesible(map)) {
        if(!findElement(closedSet,cur)) {
            int g = parent->getG() + cur->getCost();
            int h = cur->calculateH2(target);
            cur->setG(g);
            if(!findElement(openSet, cur)) {
                if(cur->getG() < parent->getG()){
                    if(cur->getPoint()==target->getPoint()){
                        target->setParent(parent);
                    }
                    openSet.remove(cur);
                    cur->setParent(parent);
                    cur->setG(g);
                    cur->setH(h);
                    cur->setF(g+h);
                    openSet.push_back(cur);
                    openSet.sort(sort_by_f);
                
                } else {
                    if(cur->getPoint() == target->getPoint()){
                        target->setParent(parent);
                    }
                    cur->setG(g);
                    cur->setH(h);
                    cur->setF(g+h);
                    cur->setParent(parent);
                    openSet.push_back(cur);
                    openSet.sort(sort_by_f);
                }
            }
        }
    }
}


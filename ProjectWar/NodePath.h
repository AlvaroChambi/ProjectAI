//
//  NodePathPath.h
//  ProjectWar
//
//  Created by Pablo Luis Gutierrez on 22/04/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#ifndef __ProjectWar__NodePath__
#define __ProjectWar__NodePath__

#include <stdio.h>
#include "Point.h"
#include "Map.h"
#include <math.h>
#include <algorithm>


class NodePath {
public:
    NodePath() : parent(nullptr), cost(1), f(0), g(0), h(0)
    {
        
    }
    
    Point getPoint()
    {
        return point;
    }
    
    void setPoint(Point point)
    {
        this->point = point;
    }
    
    NodePath* getParent()
    {
        return parent;
    }
    
    void setParent(NodePath* parent)
    {
        this->parent = parent;
    }
    
    float getCost()
    {
        return cost;
    }
    
    void setF(int f)
    {
        this->f = f;
    }
    
    void setG(int g)
    {
        this->g = g;
    }
    
    void setH(int h)
    {
        this->h = h;
    }
    
    int getF() const
    {
        return this->f;
    }
    
    int getG()
    {
        return this->g;
    }
    
    int getH()
    {
        return this->h;
    }
    
    int calculateH(NodePath *target)
    {
        return sqrt( ((target->getPoint().x)-(this->getPoint().x))*((target->getPoint().x)-(this->getPoint().x))
                    + ((target->getPoint().y)-(this->getPoint().y))*((target->getPoint().y)-(this->getPoint().y)));
    }
    
    int calculateH2(NodePath *target)
    {
        int dx = abs(target->getPoint().x - this->getPoint().x), dy = abs(target->getPoint().y - this->getPoint().y);
        return abs(dx - dy) + sqrt(2) * std::min(dx, dy);
    }
    
    int calculateH3(NodePath *target)
    {
        return point.distance(target->getPoint());
    }

    void setCost(float cost)
    {
        this->cost = cost;
    }
     
    bool accesible(Map* map)
    {
        /*
        bool accesible = true;
        if(point.x <0 || point.y<0){
            accesible = false;
        }else{
            InfoTile* infoTile = map->getInfoMap()[point.x][point.y];
            if(infoTile->entity==UNIT_ENTITY) {
                accesible = false;
            }
        }
        return accesible;*/
        return true;
    }
    
    
private:

    Point point;
    NodePath *parent;

    int cost;
    int f,g,h;
};


#endif /* defined(__ProjectWar__NodePath__) */

//
//  LinkedList.h
//  ProjectWar
//
//  Created by Pablo Luis Gutierrez on 17/03/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#ifndef __ProjectWar__LinkedList__
#define __ProjectWar__LinkedList__

#include <stdio.h>
#include <stdlib.h>
#include "Texture.h"


class Node
{
public:
    Node():value(nullptr), next(nullptr)
    {
    }
    
    Texture *value;
    Node *next;
};



class LinkedList
{
public:
    LinkedList();
    ~LinkedList();
    void insertTexture(Texture *v);
    void deleteTexture(Texture *v);
    int emptyList();
    void deleteList();
    void showList();
    
private:
    Node *list;
    
};

#endif /* defined(__ProjectWar__LinkedList__) */

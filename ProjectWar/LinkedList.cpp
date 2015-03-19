//
//  LinkedList.cpp
//  ProjectWar
//
//  Created by Pablo Luis Gutierrez on 17/03/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#include "LinkedList.h"



LinkedList::LinkedList():list( NULL)
{
    
}

LinkedList::~LinkedList()
{
    
}
/* Insert a new texture sorting by z_order*/

void LinkedList::insertTexture(Texture *v)
{
    Node *newNode, *previousNode;
    
    newNode = new Node;
    newNode->value = v;
    
    if(emptyList() || (*list).value->getZOrder() > v->getZOrder()) {
        /* Add to the list next to the new node */
        newNode->next = list;
        /* Then, the start of the list is the new node */
        list = newNode;
    } else {
        /* Look for the node previous with less value than v*/
        previousNode = list;

        while(previousNode->next && previousNode->next->value->getZOrder() <= v->getZOrder())
            previousNode = previousNode->next;

        newNode->next = previousNode->next;
        previousNode->next = newNode;
    }
}

void LinkedList::deleteTexture(Texture *v)
{
    Node *previousNode, *node;
 
    node = list;
    previousNode = NULL;
    while(node && node->value->getZOrder() < v->getZOrder()) {
        previousNode = node;
        node = node->next;
    }
    if(!node || node->value->getZOrder() != v->getZOrder()) return;
    else {
    
        if(!previousNode)
            list = node->next;
        else
            previousNode->next = node->next;
    }
}

int LinkedList::emptyList()
{
    return (list == NULL);
}

void LinkedList::deleteList()
{
    Node *node;
    
    while(list) {
        node = list;
        list = node->next;
        free(node);
    }
}

void LinkedList::showList()
{
    Node *node = list;
    
    if(!emptyList()){
        while(node) {
            printf("%d -> ", node->value->getZOrder());
            node = node->next;
        }
    }
}
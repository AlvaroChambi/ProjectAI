//
//  Node.h
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 9/9/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#ifndef __ProjectWar__Node__
#define __ProjectWar__Node__

#include <stdio.h>
#include <vector>

template <class T>
class Node {
    
public:
    Node() : item(nullptr)
    {}
    ~Node()
    {}
    
    T item;
    std::vector<Node*> childs;
    
    void addChild(T child)
    {
        Node<T>* node = new Node<T>;
        node->item = child;
        childs.push_back(node);
    }
};

#endif /* defined(__ProjectWar__Node__) */

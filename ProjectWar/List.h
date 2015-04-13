//
//  List.h
//  ProjectWar
//
//  Created by Pablo Luis Gutierrez on 17/03/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#ifndef __ProjectWar__List__
#define __ProjectWar__List__

#include <stdio.h>
#include <stdlib.h>

template <class T>

class Node
{
public:
    Node() : next(nullptr), order(0)
    {
    }
    
    T value;
    Node *next;
    int order;
};

template <class T>
class List
{
public:
    List():list(nullptr), size(0){}
    ~List(){}
    //TODO implement method contains(T) that returns true if the given object is  already in the list
    //TODO implement remove(T)
    void add(T value)
    {
        Node<T> *newNode, *previousNode;
        
        newNode = new Node<T>;
        newNode->value = value;
        if(isEmpty()) {
            /* Add to the list next to the new node */
            newNode->next = list;
            
            /* Then, the start of the list is the new node */
            list = newNode;
        } else {
            previousNode = list;
            
            while(previousNode->next)
                previousNode = previousNode->next;
            
            newNode->next = previousNode->next;
            previousNode->next = newNode;
        }
        size++;
    }
    void insert(T value, int order)
    {
        
        Node<T> *newNode, *previousNode;
        
        newNode = new Node<T>;
        newNode->value = value;
        newNode->order = order;
        
        if(isEmpty() || (*list).order > order) {
            /* Add to the list next to the new node */
            newNode->next = list;
            
            /* Then, the start of the list is the new node */
            list = newNode;
        } else {
            /* Look for the node previous with less value than v*/
            previousNode = list;
            
            while(previousNode->next && previousNode->next->order <= order)
                previousNode = previousNode->next;
            
            newNode->next = previousNode->next;
            previousNode->next = newNode;
        }
        size++;
    }
    
    bool isEmpty()
    {
        return (list == nullptr);
    }
    
    T getElement(int position)
    {
        Node<T> *node = list;
        Node<T> *ret;
        int cont=0;
        if(!isEmpty()){
            while(node) {
                if(cont<position){
                    node = node->next;
                    cont++;
                }
                else{
                    ret = node;
                    node = nullptr;
                }
            }
        }
        return ret->value;
    }
    
    T getElementOrder(int order)
    {
        Node<T> *node = list;
        Node<T> *ret;
        if(!isEmpty()){
            while(node) {
                if(node->order!=order){
                    node = node->next;
                }
                else{
                    ret = node;
                    node=nullptr;
                }
            }
        }
        return ret->value;
    }
    
    int getSize()
    {
        return size;
    }
    
    void deleteList()
    {
        Node<T> *node;
        
        while(list) {
            node = list;
            list = node->next;
            free(node);
        }
        size = 0;
    }
    
    void showList()
    {
        Node<T> *node = list;
        
        if(!isEmpty()){
            while(node) {
                printf("%d -> ", node->order);
                node = node->next;
            }
        }
    }
    
private:
    Node<T> *list;
    int size;
    
};

#endif /* defined(__ProjectWar__List__) */

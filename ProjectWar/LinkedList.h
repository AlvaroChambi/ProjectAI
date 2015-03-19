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


typedef struct _nodo {
    //int valor;
    Texture *valor;
    struct _nodo *siguiente;
} tipoNodo;

typedef tipoNodo *pNodo;
typedef tipoNodo *Lista;

class LinkedList
{
public:
    LinkedList();
    ~LinkedList();
    void Insertar(Texture *v);
    void Borrar(Lista *lista, Texture *v);
    int ListaVacia();
    void BorrarLista(Lista *lista);
    void MostrarLista();
    
private:
    Lista lista;
    
};

#endif /* defined(__ProjectWar__LinkedList__) */

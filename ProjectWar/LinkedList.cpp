//
//  LinkedList.cpp
//  ProjectWar
//
//  Created by Pablo Luis Gutierrez on 17/03/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#include "LinkedList.h"



LinkedList::LinkedList()
{
     lista = NULL;
}

LinkedList::~LinkedList()
{
    
}

void LinkedList::Insertar(Texture *v) {
    pNodo nuevo, anterior;
    
    /* Crear un nodo nuevo */
    nuevo = (pNodo)malloc(sizeof(tipoNodo));
    nuevo->valor = v;
    
    /* Si la lista está vacía */
    if(ListaVacia() || (*lista).valor->getZ_order() > v->getZ_order()) {
        /* Añadimos la lista a continuación del nuevo nodo */
        nuevo->siguiente = lista;
        /* Ahora, el comienzo de nuestra lista es en nuevo nodo */
        lista = nuevo;
    } else {
        /* Buscar el nodo de valor menor a v */
        anterior = lista;
        /* Avanzamos hasta el último elemento o hasta que el siguiente tenga
         un valor mayor que v */
        while(anterior->siguiente && anterior->siguiente->valor->getZ_order() <= v->getZ_order())
            anterior = anterior->siguiente;
        /* Insertamos el nuevo nodo después del nodo anterior */
        nuevo->siguiente = anterior->siguiente;
        anterior->siguiente = nuevo;
    }
}

void LinkedList::Borrar(Lista *lista, Texture *v) {
    pNodo anterior, nodo;
 /*
    nodo = *lista;
    anterior = NULL;
    while(nodo && nodo->valor->getZ_order() < v->getZ_order) {
        anterior = nodo;
        nodo = nodo->siguiente;
    }
    if(!nodo || nodo->valor->getZ_order() != v->getZ_order) return;
    else { /* Borrar el nodo */
    
    //    if(!anterior) /* Primer elemento */
      //      *lista = nodo->siguiente;
       // else  /* un elemento cualquiera */
        //    anterior->siguiente = nodo->siguiente;
        //free(nodo);
   // }
}

int LinkedList::ListaVacia() {
    return (lista == NULL);
}

void LinkedList::BorrarLista(Lista *lista) {
    pNodo nodo;
    
    while(*lista) {
        nodo = *lista;
        *lista = nodo->siguiente;
        free(nodo);
    }
}

void LinkedList::MostrarLista() {
    pNodo nodo = lista;
    
    if(ListaVacia()) printf("Lista vacía\n");
    else {
        while(nodo) {
            printf("%d -> ", nodo->valor->getZ_order());
            nodo = nodo->siguiente;
        }
    }
}
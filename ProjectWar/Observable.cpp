//
//  Observable.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 15/3/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#include "Observable.h"
#include <iostream>

Observable::Observable() : numListeners(0)
{
   
}

Observable::~Observable()
{

}

void Observable::registerObserver( Observer* observer )
{
    observers[numListeners] = observer;
    numListeners++;
}

void Observable::unRegisterObserver( Observer* observer )
{
    //TODO remove observer from the list
}

void Observable::notifyObservers()
{
    for (int i = 0; i < numListeners; i++) {
        observers[i]->update();
    }
}

void Observable::notify(Observer* observer)
{
    observer->update();
}
//
//  Observable.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 15/3/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#include "Observable.h"
#include <iostream>

Observable::Observable()
{
   
}

Observable::~Observable()
{

}

void Observable::registerObserver( Observer* observer )
{
    observers.add(observer);
}

void Observable::unRegisterObserver( Observer* observer )
{
    //TODO remove observer from the list
}

void Observable::notifyObservers(Update update)
{
    for (int i = 0; i < observers.getSize(); i++) {
        observers.getElement(i)->update(update);
    }
}

//Don't really know why is this here...
void Observable::notify(Observer* observer)
{
    //observer->update();
}
//
//  Observable.h
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 15/3/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#ifndef __ProjectWar__Observable__
#define __ProjectWar__Observable__

#include <stdio.h>
#include <vector>
#include <list>

#include "Observer.h"

class Observable
{
public:
    Observable();
    virtual ~Observable();
    void registerObserver( Observer* observer );
    void unRegisterObserver( Observer* observer );
    void notifyObservers(Update update);
    void notify(Observer* observer);
private:
    std::list <Observer*> observers;
};

#endif /* defined(__ProjectWar__Observable__) */


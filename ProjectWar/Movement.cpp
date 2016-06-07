//
//  Movement.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 22/4/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#include "Movement.h"

Movement::Movement() {

}

Movement::~Movement() {

}

void Movement::execute() {
    for ( Action* action : actions ) {
        action->execute();
    }
}

void Movement::cancel() {
    for ( Action* action : actions ) {
        action->cancel();
    }
}



//
//  Action.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 01/06/16.
//  Copyright (c) 2016 Alvaro Chambi Campos. All rights reserved.
//

#include "Action.h"

Action::Action() {

}

Action::~Action() {

}

void Action::execute() {
    for ( Command* command : commands ) {
        command->execute();
    }
}

void Action::cancel() {
    for ( Command* command : commands ) {
        command->cancel();
    }
}
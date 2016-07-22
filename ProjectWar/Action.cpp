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
    commands.clear();
}

void Action::execute() {
    for ( Command* command : commands ) {
        command->execute();
    }
}

void Action::cancel() {
    int i;
    for (i=commands.size()-1; i>=0; i--){
        commands.at(i)->cancel();
    }
}
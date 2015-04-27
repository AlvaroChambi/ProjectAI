//
//  Movement.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 22/4/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#include "Movement.h"

Movement::Movement() : commands(), score(0)
{

}

Movement::Movement(int score) : commands(), score(score)
{

}

Movement::Movement(List<Command*>* commands, int score) : commands(commands), score(score)
{
    
}

Movement::~Movement()
{

}

void Movement::execute()
{
    std::cout << "      Movement executed\n";
    for (int i = 0; i < commands->getSize(); i++) {
        Command* command = commands->getElement(i);
        command->execute();
    }
}

void Movement::cancel()
{
    std::cout << "      Movement canceled\n";
    for (int i = 0; i < commands->getSize(); i++) {
        Command* command = commands->getElement(i);
        command->cancel();
    }
}




//
//  MoveCommand.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 21/3/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#include "MoveCommand.h"

MoveCommand::MoveCommand(Unit* unit) : unit(unit)
{

}

MoveCommand::~MoveCommand()
{

}

void MoveCommand::execute()
{
    std::cout << "executing move command";
}

void MoveCommand::cancel()
{
    std::cout << "canceling move command";
}
//
//  PlayerAI.cpp
//  ProjectWar
//
//  Created by Pablo Luis Gutierrez on 09/04/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#include "PlayerAI.h"


PlayerAI::PlayerAI()
{
    
}

PlayerAI::~PlayerAI()
{

}

List<Command> PlayerAI::play()
{
    List<Command> commandsList;
    List<Unit*> unitsList = this->getUnitList();
    int random = rand() %5;
    
    for(int i=0; i< unitsList.getSize(); i++){
        
        unitsList.getElement(i)->getPosition();
    }
    
    return commandsList;
    
}
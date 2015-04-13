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
    int random1 = rand()%3;
    int random2 = rand()%3;
    Point point;
    for(int i=0; i< unitsList.getSize(); i++){
        point = unitsList.getElement(i)->getPosition();
        point.x +=random1;
        point.y +=random2;
        /*
        if(unitsList.getElement(i)->canAttack(point)){
            commandsList.add(new AttackCommand());
        }
         */
        if (unitsList.getElement(i)->canReach(point)) {
            commandsList.add(*new MoveCommand(unitsList.getElement(i),this->getMap(),point));

        }
    }
    
    return commandsList;
    
}
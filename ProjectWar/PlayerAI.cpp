//
//  PlayerAI.cpp
//  ProjectWar
//
//  Created by Pablo Luis Gutierrez on 09/04/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#include "PlayerAI.h"
#include "Map.h"

PlayerAI::PlayerAI() : Player()
{
    setType(AI_PLAYER);
}

PlayerAI::PlayerAI(int id) : Player(id)
{
    setType(AI_PLAYER);
}

PlayerAI::~PlayerAI()
{

}

List<Command*> PlayerAI::play()
{
    List<Command*> commandsList;
    List<Unit*> unitsList = this->getUnitList();
    int random1 = rand()%3;
    int random2 = rand()%3;
    Unit* unit = nullptr;
    Point point;
    for(int i=0; i< unitsList.getSize(); i++){
        unit = unitsList.getElement(i);
        point = unit->getPosition();
        point.x +=random1;
        point.y +=random2;
        /*
        if(unitsList.getElement(i)->canAttack(point)){
            commandsList.add(new AttackCommand());
        }
         */
        if (unitsList.getElement(i)->canReach(point)) {
            //commandsList.add(new MoveCommand(unitsList.getElement(i),this->getMap(),point));
            if(point.x < 15 && point.y < 10){
                Command* command = new MoveCommand(unit,this->getMap(),point);
                command->execute();
            }
        }
    }
    /*
    for (int i = 0; i < commandsList.getSize(); i++) {
        commandsList.getElement(i)->execute();
    }*/
    
    return commandsList;
}
//
//  PlayerAI.cpp
//  ProjectWar
//
//  Created by Pablo Luis Gutierrez on 09/04/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#include "PlayerAI.h"
#include "Map.h"
#include "NodePath.h"
#include <set>
#include "Pathfinder.h"




PlayerAI::PlayerAI() : Player(), playersList(nullptr)
{
    setType(AI_PLAYER);
}

PlayerAI::PlayerAI(int id) : Player(id), playersList(nullptr)
{
    setType(AI_PLAYER);
}

PlayerAI::~PlayerAI()
{

}

void PlayerAI::setPlayerList(List<Player*> *players)
{
    this->playersList = players;
}


List<Command*> PlayerAI::play()
{
    List<Command*> commandsList;
    List<Unit*> unitsList = this->getUnitList();

    Unit* unit = nullptr;
    Point point;
    
   
    Pathfinder *pathfinder = new Pathfinder(this->getMap());
    std::list<NodePath*> path;
    path = pathfinder->find(2, 2, 5, 9);
    
    std::list<NodePath*>::iterator it;
    
    NodePath* nod;
    
 
    std::cout << "myset contains:";
    for (it=path.begin(); it!=path.end(); ++it){
        nod=*it;
        std::cout << ' ' << nod->getPoint()->x;
        std::cout << '-';
        std::cout << ' ' << nod->getPoint()->y;
    }
    std::cout << '\n';
    

    
    
    for(int i=0; i< unitsList.getSize(); i++){
        unit = unitsList.getElement(i);
        point = unit->getPosition();
        point.x +=2;
        point.y +=1;
        /*
        if(unitsList.getElement(i)->canAttack(point)){
            commandsList.add(new AttackCommand());
        }
         */
        
        //Command* command = new MoveCommand(unit,this->getMap(),point);
        //command->execute();
        
        if (unit->canReach(point)) {
            //commandsList.add(new MoveCommand(unitsList.getElement(i),this->getMap(),point));
            if(point.x < 15 && point.y < 10){
                if(canAttack(unit).getSize()>0){
                    List<Unit*> list = canAttack(unitsList.getElement(i));
                      Command* command = new AttackCommand(unit,list.getElement(0));
                    command->execute();
                    }
                  //
                else if(canConquer(unit).getSize()>0){
                    List<Building*> listBuild = canConquer(unitsList.getElement(i));
                    if(listBuild.getElement(0)->getPosition().x != unit->getPosition().x || listBuild.getElement(0)->getPosition().y != unit->getPosition().y){
                        Command* command = new MoveCommand(unit,this->getMap(),listBuild.getElement(0)->getPosition());
                        command->execute();
                    }
                    Command* command = new CaptureCommand(this,unit,listBuild.getElement(0));
                    command->execute();
                    
                }
                
            }
            
                Command* command = new MoveCommand(unit,this->getMap(),point);
                //command->execute();
            }
        }
    
    /*
    for (int i = 0; i < commandsList.getSize(); i++) {
        commandsList.getElement(i)->execute();
    }*/
    
    return commandsList;
}
List<Unit*> PlayerAI::canAttack(Unit *unit)
{
    List<Unit*> unitList;
    int x = unit->getPosition().x - unit->getAttackRange();
    int y = unit->getPosition().y - unit->getAttackRange();

    
    for (int i = x; i <= x + (unit->getAttackRange() * 2) ; i++) {
        for (int j = y; j <= y + (unit->getAttackRange() * 2) ; j++) {
            int distance = std::abs(unit->getPosition().x - i) + std::abs(unit->getPosition().y - j);
            if(distance >= 0 && distance <= unit->getAttackRange() && i >= 0 && j >= 0){
                if(i >= 0 && i < MAP_WIDTH && j >= 0 && j < MAP_HEIGHT){
                    InfoTile* infoTile = this->getMap()->getInfoMap()[i][j];
                    
                    if(infoTile->ownerID != -1 && infoTile->ownerID != this->getId()){
                        
                        for(int k=0; k<playersList->getSize();k++){
                            if(playersList->getElement(k)->getId()==infoTile->ownerID)
                            {
                                unitList.add(playersList->getElement(k)->getUnit(infoTile->unitID));
                                
                            }
                        
                        }
                    }
                }
            }
        }
    }
    return unitList;
}

List<Building*> PlayerAI::canConquer(Unit *unit)
{
    List<Building*> buildingList;
    int x = unit->getPosition().x - unit->getMovement();
    int y = unit->getPosition().y - unit->getMovement();
    
    for (int i = x; i <= x + (unit->getMovement() * 2) ; i++) {
        for (int j = y; j <= y + (unit->getMovement() * 2) ; j++) {
            int distance = std::abs(unit->getPosition().x - i) + std::abs(unit->getPosition().y - j);
            if(distance >= 0 && distance <= unit->getMovement() && i >= 0 && j >= 0){
                if(i >= 0 && i < MAP_WIDTH && j >= 0 && j < MAP_HEIGHT){
                    InfoTile* infoTile = this->getMap()->getInfoMap()[i][j];
                    if(infoTile->entity==BUILDING_ENTITY) {
                        if(infoTile->ownerID != -1 || infoTile->ownerID != this->getId()){
                            
                            Building *building=this->getMap()->getBuilding(Point(i,j));
                            buildingList.add(building);
                            
                        }
                    }
                }
            }
        }
    }
    
    
    return buildingList;
}



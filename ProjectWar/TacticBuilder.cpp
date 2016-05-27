//
//  TacticBuilder.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 25/4/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#include "TacticBuilder.h"
#include "MoveCommand.h"
#include "CaptureCommand.h"
#include "AttackCommand.h"
#include "Map.h"
#include "Pathfinder.h"
#include "Path.h"

TacticBuilder::TacticBuilder(GameState* game) : game(game), count(0)
{

}

TacticBuilder::~TacticBuilder()
{

}

void TacticBuilder::resetInfluenceMap()
{
    for (int i =0; i<MAP_HEIGHT; i++) {
        for (int j = 0; j<MAP_WIDTH; j++) {
            influenceMap[i][j]=0;
        }
    }
}

void TacticBuilder::printInfluenceMap()
{
    for (int i = 0; i<10; i++) {
        for (int j=0; j<15; j++) {
            std::cout << influenceMap[i][j];
        }
        std::cout <<"\n";
    }
}

void TacticBuilder::calculateInfluenceMap(Player* player, Player* enemy)
{
    resetInfluenceMap();
    std::list<Player*> players;
    players.push_back(enemy);
    players.push_back(player);
    for (Player* player : players) {
        for(Unit* unit : player->getAliveUnits()){
            int posX = unit->getPosition().x;
            int posY = unit->getPosition().y;
            int x = unit->getPosition().x - unit->getMovement();
            int y = unit->getPosition().y - unit->getMovement();
            
            for (int i = x; i <= x + (unit->getMovement() * 2) ; i++) {
                for (int j = y; j <= y + (unit->getMovement() * 2) ; j++) {
                    int distance = std::abs(unit->getPosition().x - i) + std::abs(unit->getPosition().y - j);
                    if(distance >= 0 && distance <= unit->getMovement()){
                        if( i >= 0 && i < MAP_WIDTH && j >= 0 && j < MAP_HEIGHT ){ //Avoiding negative and outside map positions
                            if(player->getType()==AI_PLAYER){
                                Path *path = player->getMap()->getPath(Point (i,j), Point (posX,posY));
                                influenceMap[j][i]+=unit->getHP()*unit->getAttackRange() - path->size();
                            } else{
                                Path *path = player->getMap()->getPath(Point (i,j), Point (posX,posY));
                                influenceMap[j][i]-=unit->getHP()*unit->getAttackRange() - path->size();
                            }
                        }
                    }
                }
            }
        }
    }
}



Tactic* TacticBuilder::createTactic(Player* player, Player* enemy, std::string gray)
{
    Tactic* tactic= new Tactic(ATTACK_TACTIC);
    for (Unit* unit : player->getAliveUnits()) {
        char c= gray.back();
        gray.pop_back();
        switch (c) {
            case 'A':
            {
                genUnitMovement(unit, player, enemy, tactic, ATTACK_TACTIC);
            }
            break;
            case 'C':
            {
                genUnitMovement(unit, player, enemy, tactic, CAPTURE_TACTIC);
            }
            break;
        
        }
    }
    
    return tactic;
}


void TacticBuilder::genUnitMovement(Unit *unit, Player *player, Player *enemy, Tactic *tactic, TacticType type)
{
    std::list<Command*>* commands = new std::list<Command*>;
    Map* map = player->getMap();
    MoveCommand* move = nullptr;
    switch (type) {
        case ATTACK_TACTIC:
        {
            
            //If can reach some enemy unit
            Unit* target = getTarget(unit, enemy);
            if (target != nullptr) {
                //Get path to the given target
                Path* path = map->getPath(unit->getPosition(), target->getPosition());
                //Get the previous to last node
                if(path->size() >= 2){
                    Point destination = path->getNode(path->size() - 2)->getPoint();
                    move = new MoveCommand(unit, map, destination);
                    //create attack command
                    AttackCommand* attack = new AttackCommand(unit, target,player->getMap());
                    commands->push_back(move);
                    commands->push_back(attack);
                }
                else{
                    AttackCommand* attack = new AttackCommand(unit, target,player->getMap());
                    commands->push_back(attack);
                }

            }else{
                //else pick some enemy unit and get a path to reach it
                target = enemy->getAliveUnits().front();
                //create a move command with the given path
                Path* path = map->getUnitPath(unit, target->getPosition());
                Point destination = path->getLastNode()->getPoint();
                move = new MoveCommand(unit, map, destination);
                commands->push_back(move);
            }
        }
            break;
        case CAPTURE_TACTIC:
        {
            //Get the nearest building that the player hasn't captured yet
            
            Building* building = getBuilding(player, unit, map);   
            if(building!= nullptr){
            
            if (unit->canReach(building->getPosition())) {
                //create a capture command
                move = new MoveCommand(unit, map, building->getPosition());
                CaptureCommand* capture = new CaptureCommand(player,unit, building);
                commands->push_back(move);
                commands->push_back(capture);
            }
            else{
                 //create a move command with the given path
                Path* path = map->getUnitPath(unit, building->getPosition());
                Point destination = path->getLastNode()->getPoint();
                move = new MoveCommand(unit, map, destination);
                commands->push_back(move);
            }
            }
            
                
           
            
        }
            break;
        default:
            break;
    }
    Movement* movement = new Movement(commands);
    tactic->addMovement(movement);
}

Unit* TacticBuilder::getTarget(Unit* unit, Player* enemy)
{
    Unit* result = nullptr;

    std::vector<Unit*>::iterator iterator = enemy->getAliveUnits().begin();
    std::vector<Unit*>::iterator end = enemy->getAliveUnits().end();
    bool targetFound = false;
    while(iterator != end && !targetFound){
        Unit* target = *iterator;
        if (unit->canAttack(target)) {
            targetFound = true;
            result = target;
        }
        iterator++;
    }
    return result;
}

Building* TacticBuilder::getBuilding(Player* player, Unit* unit, Map* map)
{
    Building* result = nullptr;
    int shortestDistance = std::numeric_limits<int>::max();
    int nearestBuilding = -1;
    //find nearest building to the unit
    for (Building* building : map->getBuildings()) {
        int distance = unit->getPosition().distance(building->getPosition());
        if ( distance < shortestDistance && !building->isCaptured(player->getId()) ){
            shortestDistance = distance;
            nearestBuilding = building->getId();
        }
    }
    result = map->getBuilding(nearestBuilding);
    return result;
}
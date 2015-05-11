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

TacticBuilder::TacticBuilder(GameState& game) : game(game), count(0)
{

}

TacticBuilder::~TacticBuilder()
{

}

Tactic* TacticBuilder::createTactic(TacticType type, Player* player, Player* enemy)
{
    Tactic* tactic = new Tactic(type);
    buildTactic(player, enemy, tactic);
    return tactic;
}

void TacticBuilder::buildTactic(Player* player, Player* enemy ,Tactic *tactic)
{
    //for each unit generate a movement
    for (Unit* unit : player->getUnitList()) {
        genUnitMovement(unit, player, enemy, tactic);
    }
}

void TacticBuilder::genUnitMovement(Unit *unit, Player *player, Player* enemy, Tactic *tactic)
{
    std::list<Command*>* commands = new std::list<Command*>;
    Map* map = player->getMap();
    MoveCommand* move = nullptr;
    switch (tactic->type) {
        case ATTACK_TACTIC:
        {
            //If can reach some enemy unit
            Unit* target = getTarget(unit, enemy);
            if (target != nullptr) {
                //Get path to the given target
                Path* path = map->getPath(unit->getPosition(), target->getPosition());
                //Get the previous to last node
                Point destination = path->getNode(path->size() - 2)->getPoint();
                std::cout << "Unit " << unit->getId() << " to target "<< target->getPosition() <<"(attack)\n";
                path->printPath();
                move = new MoveCommand(unit, map, destination);
                //create attack command
                AttackCommand* attack = new AttackCommand(unit, target);
                commands->push_back(move);
                commands->push_back(attack);
            }else{
                //else pick some enemy unit and get a path to reach it
                target = enemy->getUnitList().front();
                //create a move command with the given path
                Path* path = map->getUnitPath(unit, target->getPosition());
                std::cout << "Unit " << unit->getId() << " to target "<< target->getPosition() <<"\n";
                path->printPath();
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
            if (unit->canReach(building->getPosition())) {
                //create a capture command
                move = new MoveCommand(unit, map, building->getPosition());
                CaptureCommand* capture = new CaptureCommand(player,unit, building);
                commands->push_back(move);
                commands->push_back(capture);
            }else{
                 //create a move command with the given path
                Path* path = map->getUnitPath(unit, building->getPosition());
                std::cout << "Unit " << unit->getId() << " to building " << building->getPosition() <<"\n";
                path->printPath();
                Point destination = path->getLastNode()->getPoint();
                move = new MoveCommand(unit, map, destination);
                commands->push_back(move);
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
    std::list<Unit*>::iterator iterator = enemy->getUnitList().begin();
    std::list<Unit*>::iterator end = enemy->getUnitList().end();
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
    int shortestDistance = INFINITY;
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
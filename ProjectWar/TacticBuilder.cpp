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

TacticBuilder::TacticBuilder(GameState& game) : game(game), count(0)
{

}

TacticBuilder::~TacticBuilder()
{

}

Tactic* TacticBuilder::createTactic(TacticType type, Player* player, Player* enemy)
{
    Tactic* tactic = new Tactic(count++);
    switch (type) {
        case ATTACK_TACTIC:
            tactic->type = type;
            tactic->attackScore = 10;
            tactic->captureScore = 5;
            tactic->moveScore = 0;
            break;
        case CAPTURE_TACTIC:
            tactic->type = type;
            tactic->captureScore = 10;
            tactic->attackScore = 5;
            tactic->moveScore = 0;
            break;
        default:
            break;
    }
    buildTactic(player, enemy, tactic);
    return tactic;
}

void TacticBuilder::buildTactic(Player* player, Player* enemy ,Tactic *tactic)
{
    for (Unit* unit : player->getUnitList()) {
        genMovements(unit, player, enemy, tactic);
    }
}

bool sort_by_score (Movement* first, Movement* second)
{
    if( first->getScore()< second->getScore())
        return true;
    else
        return false;
}

void TacticBuilder::genMovements(Unit *unit, Player *player, Player *enemy, Tactic*tactic)
{
    Map* map = player->getMap();
    std::list<Movement*>* movements = new std::list<Movement*>();
    std::list<Command*>* commands = new std::list<Command*>;
    
    for (Unit* target : enemy->getUnitList()) {
        int targetUnit = -1;
        if (unit->canAttack(target) && target->getHP() > 0) {
            //generate move and attack command
            targetUnit = target->getId();
            MoveCommand* move = nullptr;
            int incrementX[4] = {1,-1, 0, 0};
            int incrementY[4] = {0, 0, 1,-1};
            for (int i = 0; i < 4; i++) {
                int posX = target->getPosition().x + incrementX[i];
                int posY = target->getPosition().y + incrementY[i];
                Point destination = Point(posX, posY);
                if (unit->canReach(destination) && map->isValidPosition(destination)) {
                    move = new MoveCommand(unit, map, destination);
                }
                
            }
            commands->push_back(move);
            commands->push_back(new AttackCommand(unit, enemy->getUnit(targetUnit)));
            movements->push_back(new Movement(commands, tactic->attackScore));
            movements->sort(sort_by_score);
        }
    }
    if (commands->empty()) {
        std::list<Unit*>::iterator it;
        it = enemy->getUnitList().begin();
        Unit* target = *it;
        Pathfinder* pathfinder = new Pathfinder(player->getMap());
        Point origin = unit->getPosition();
        Point destination = target->getPosition();
        std::list<NodePath*> nodes = pathfinder->find(origin.x, origin.y, destination.x, destination.y);
        
        pathfinder->printList(nodes);
        
        std::list<NodePath*>::iterator iterator;
        iterator = nodes.begin();
        std::advance(iterator,unit->getMovement());
        NodePath* node = *iterator;
        MoveCommand* move = new MoveCommand(unit, map, node->getPoint());
        commands->push_back(move);
        movements->push_back(new Movement(commands, tactic->attackScore));
        movements->sort(sort_by_score);
    }
    
    for (Building* building : map->getBuildings()) {
        std::list<Command*>* commands = new std::list<Command*>;
        //if the unit can reach the building and the player doesn't already own it add the movement
        if (unit->canReach(building->getPosition()) && !building->isCaptured(player->getId())) {
            //Generate move and capture command
            MoveCommand* move = new MoveCommand(unit,map,building->getPosition());
            CaptureCommand* capture = new CaptureCommand(player, unit, building);
            commands->push_back(move);
            commands->push_back(capture);
            movements->push_back(new Movement(commands, tactic->captureScore));
            movements->sort(sort_by_score);
        }else{
            //Go to the nearest posible position to the building
            Pathfinder pathfinder;
            Point origin = unit->getPosition();
            Point destination = building->getPosition();
            std::list<NodePath*> nodes = pathfinder.find(origin.x, origin.y, destination.x, destination.y);
            
            std::list<NodePath*>::iterator iterator;
            iterator = nodes.begin();
            std::advance(iterator, unit->getMovement());
            
            NodePath* node = *iterator;
            MoveCommand* move = new MoveCommand(unit, map, node->getPoint());
            commands->push_back(move);
            movements->push_back(new Movement(commands, tactic->captureScore));
            movements->sort(sort_by_score);
        }
        
    }
    
    tactic->addMovement(movements->front());
}
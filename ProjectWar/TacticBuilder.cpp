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
    for (int i = 0; i < player->getUnitList().getSize(); i++) {
        Unit* unit = player->getUnitList().getElement(i);
        genMovements(unit, player, enemy, tactic);
    }
}

void TacticBuilder::genMovements(Unit *unit, Player *player, Player *enemy, Tactic*tactic)
{
    Map* map = player->getMap();
    List<Movement*>* movements = new List<Movement*>();
    
    for (int i = 0; i < enemy->getUnitList().getSize(); i++) {
        Unit* target = enemy->getUnitList().getElement(i);
        int targetUnit = -1;
        if (unit->canAttack(target) && target->getHP() > 0) {
            //generate move and attack command
            targetUnit = target->getId();
            List<Command*>* commands = new List<Command*>;
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
            commands->add(move);
            commands->add(new AttackCommand(unit, enemy->getUnit(targetUnit)));
            movements->insert(new Movement(commands, tactic->attackScore), tactic->attackScore);
        }
    }
    
    for (int i = 0; i < map->getBuildings().getSize(); i++) {
        Building* building = map->getBuildings().getElement(i);
        
        //if the unit can reach the building and the player doesn't already own it add the movement
        if (unit->canReach(building->getPosition()) && !building->isCaptured(player->getId())) {
            //Generate move and capture command
            List<Command*>* commands = new List<Command*>;
            MoveCommand* move = new MoveCommand(unit,map,building->getPosition());
            CaptureCommand* capture = new CaptureCommand(player, unit, building);
            commands->add(move);
            commands->add(capture);
            movements->insert(new Movement(commands, tactic->captureScore), tactic->captureScore);
        }
    }
    
    for (int i = 0;i < map->getBuildings().getSize(); i++) {
        Building* building = map->getBuildings().getElement(i);
        
        int distance = std::abs(building->getPosition().x - unit->getPosition().x) +
        std::abs(building->getPosition().y - unit->getPosition().y);
        
        if (distance > unit->getMovement() && !building->isCaptured(player->getId())) {
            //Move towards the building
            List<Command*>* commands = new List<Command*>;
            MoveCommand* move;
            
            if (building->getPosition().x - unit->getPosition().x < 0) {
                //move left
                Point destination = Point(unit->getPosition().x - 1, unit->getPosition().y);
                move = new MoveCommand(unit, map, destination);
            }else if (building->getPosition().x - unit->getPosition().x > 0){
                //move right
                Point destination = Point(unit->getPosition().x + 1, unit->getPosition().y);
                move = new MoveCommand(unit, map, destination);
            }else if (building->getPosition().y - unit->getPosition().y < 0){
                //go up
                Point destination = Point(unit->getPosition().x, unit->getPosition().y - 1);
                move = new MoveCommand(unit, map, destination);
            }else {
                //go down
                Point destination = Point(unit->getPosition().x, unit->getPosition().y + 1);
                move = new MoveCommand(unit, map, destination);
            }
            commands->add(move);
            movements->insert(new Movement(commands, tactic->moveScore), tactic->moveScore);
        }
    }
    //For each unit just get the best option
    tactic->addMovement(movements->getElement(0));
}
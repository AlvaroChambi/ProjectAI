//
//  PlayerAI.h
//  ProjectWar
//
//  Created by Pablo Luis Gutierrez on 09/04/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#ifndef __ProjectWar__PlayerAI__
#define __ProjectWar__PlayerAI__

#include <stdio.h>
#include "Player.h"
#include "List.h"
#include "Command.h"
#include "MoveCommand.h"
#include "AttackCommand.h"
#include "CaptureCommand.h"
#include "Building.h"
#include "Movement.h"

class PlayerAI : public Player
{
public:
    PlayerAI();
    PlayerAI(int id);
    ~PlayerAI();
    void setPlayerList(List<Player*> *players);
    List<Movement*>* genMovements(Unit* unit, Player* players, Map* map);
    
    List<Command*> play ();
    List<Unit*> canAttack(Unit *unit);
    List<Building*> canConquer(Unit *unit);
    
    
private:
    List<Player*> *playersList;
};



#endif /* defined(__ProjectWar__PlayerAI__) */

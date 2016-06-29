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
#include <list>

#include "Player.h"
#include "Command.h"
#include "MoveCommand.h"
#include "AttackCommand.h"
#include "CaptureCommand.h"
#include "Building.h"
#include "Movement.h"

#include "Scene.h"

class PlayerAI : public Player
{
public:
    PlayerAI();
    PlayerAI( int id );
    ~PlayerAI();
    void setPlayerList( std::list<Player*> *players );
    std::list<Movement*>* genMovements( Unit* unit, Player* players,
                                        Map* map);
    std::list<Player*>* getPlayersList();
    
    std::list<Command*> play ();
    void executeMinimax();
    
private:
    std::list<Player*> *playersList;
};



#endif /* defined(__ProjectWar__PlayerAI__) */

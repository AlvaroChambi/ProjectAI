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

class PlayerAI : public Player
{
public:
    PlayerAI();
    ~PlayerAI();
    List<Command> play ();
    
private:

};



#endif /* defined(__ProjectWar__PlayerAI__) */

//
//  Tactic.h
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 25/4/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#ifndef __ProjectWar__Tactic__
#define __ProjectWar__Tactic__

#include <stdio.h>
#include "Movement.h"
#include "Option.h"

enum TacticType
{
    ATTACK_TACTIC,
    CAPTURE_TACTIC,
    
};

class Tactic : public Option
{
    
public:
    Tactic(TacticType type);
    Tactic( int id );
    virtual ~Tactic();
    void execute();
    void cancel();
    
    void addMovement(Movement* movement);
    
    TacticType type;
    int attackScore;
    int captureScore;
    int moveScore;
private:
    std::list<Movement*> movements;
    int id;
protected:
    
};

#endif /* defined(__ProjectWar__Tactic__) */

//
//  MovementsList.h
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 01/09/16.
//  Copyright (c) 2016 Alvaro Chambi Campos. All rights reserved.
//

#ifndef ProjectWar_MovementsList_h
#define ProjectWar_MovementsList_h

#include <vector>
#include "Movement.h"
#include "Action.h"

class MovementsList {
public:
    MovementsList( std::vector<Action*>& actions );
    ~MovementsList();
    
    void addMovement( Movement& movement );
    void reserve( int size );
    std::vector<Option*> getMovementsVector() const;
private:
    std::vector<Option*> movements;
    std::vector<Action*>& actions;
};

#endif

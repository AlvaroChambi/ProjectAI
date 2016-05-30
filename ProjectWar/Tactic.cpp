//
//  Tactic.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 25/4/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#include "Tactic.h"

Tactic::Tactic(TacticType type) : type(type), movements(), attackScore(0), captureScore(0), moveScore(0)
{

}

Tactic::Tactic(int id) : movements(), attackScore(0), captureScore(0), moveScore(0), id(id)
{

}

Tactic::~Tactic()
{

}

void Tactic::execute() {
    for (Movement* movement : movements) {
        movement->execute();
    }
}

void Tactic::cancel() {
    for (Movement* movement : movements) {
        movement->cancel();
    }
}

void Tactic::addMovement(Movement *movement)
{
    this->movements.push_back(movement);
}


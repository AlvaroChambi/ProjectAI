//
//  Tactic.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 25/4/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#include "Tactic.h"

Tactic::Tactic(int id) : movements(), attackScore(0), captureScore(0), moveScore(0), id(id)
{

}

Tactic::~Tactic()
{

}

void Tactic::execute()
{
    std::cout << "Tactic ID: " +  std::to_string(this->id) +"\n";
    std::cout << "attack score: " + std::to_string(attackScore) + "capture score" +std::to_string(captureScore) + "\n";
    for (int i = 0 ; i < movements.getSize(); i++) {
        Movement* movement = movements.getElement(i);
        movement->execute();
    }
}

void Tactic::cancel()
{
    std::cout << "Tactic ID: " +  std::to_string(this->id) +"\n";
    for (int i = 0; i < movements.getSize(); i++) {
        Movement* movement = movements.getElement(i);
        movement->cancel();
    }
}

void Tactic::addMovement(Movement *movement)
{
    this->movements.add(movement);
}


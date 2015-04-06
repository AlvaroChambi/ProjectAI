//
//  OnAttackState.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 29/3/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#include "OnAttackState.h"

OnAttackState::OnAttackState(Model* model, Command* command) : OnCommandState(model, command)
{

}

OnAttackState::~OnAttackState()
{

}

void OnAttackState::enter()
{
    //Update unit commands
}

void OnAttackState::handleInput(Input input, int id, Tile position)
{
    switch (input) {
        case ATTACK_CLICKED:
            //set unit active false
            //back to the unit selected state
            break;
        case ENEMY_UNIT_CLICKED:
            //if can reach target selected enemy
            //update attack results(maybe cancel previous executed attack command)
            
            //attack command execute
            break;
        default:
            break;
    }
}
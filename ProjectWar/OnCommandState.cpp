//
//  OnCommandState.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 29/3/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#include "OnCommandState.h"
#include "Player.h"
#include "NothingSelectedState.h"

OnCommandState::OnCommandState(Model* model, Command* command) : State(model), command(command)
{

}

OnCommandState::~OnCommandState()
{

}

void OnCommandState::handleInput(Input input, int id, Tile position)
{
    //Just handling wait and cancel states
    switch (input) {
        case WAIT_CLICKED:
        {
            //clean all previous active resources
            //set unite active false
            Player* player = (Player*) model;
            player->getSelectedUnit()->setActive(false);
            //dispose saved command
            command = nullptr;
            player->updateState(new NothingSelectedState(player));
        }
            break;
        case CANCEL_CLICKED:
        {
            //Go to the saved state
            if (command != nullptr) {
                command->cancel();
            }
        }
            break;
        default:
            //on cancel back to the previous state
            break;
    }
}
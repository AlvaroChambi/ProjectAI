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

OnCommandState::OnCommandState(Model* model, State* savedState, Command* command)
                                : State(model), command(command), savedState(savedState)
{

}

OnCommandState::~OnCommandState()
{

}

void OnCommandState::handleInput(Input input, int id, Tile position)
{
    Player* player = (Player*) model;
    //Just handling wait and cancel states
    switch (input) {
        case WAIT_CLICKED:
        {
            //set unite active false
            player->getSelectedUnit()->setActive(false);
            //dispose saved command
            command = nullptr;
            player->updateState(new NothingSelectedState(player));
        }
            break;
        case CANCEL_CLICKED:
        {
            if (command != nullptr) {
                command->cancel();
            }
            player->updateState(savedState);
        }
            break;
        default:
            break;
    }
}

void OnCommandState::cancelCommand()
{
    if(this->command != nullptr){
        this->command->cancel();
        this->command = nullptr;
    }
}

void OnCommandState::executeCommand(Command *command)
{
    Player* player = (Player*) model;
    this->command = command;
    command->execute( *player->getMap() );
}
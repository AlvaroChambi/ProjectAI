//
//  FactorySelectedState.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 11/6/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#include "FactorySelectedState.h"
#include "NothingSelectedState.h"
#include "MessageManager.h"

FactorySelectedState::FactorySelectedState(Player* player) : State(player)
{
    
}

FactorySelectedState::~FactorySelectedState()
{

}

void FactorySelectedState::enter()
{
    //TODO show ui
    MessageManager::getInstance().sendMessage(new Message(MESSAGE_SHOW_POPUP));
    std::cout << "showing factory ui...\n";
}

void FactorySelectedState::handleInput(Input input, int id, Tile position)
{
    Player* player = (Player*)model;
    switch (input) {
        default:
            std::cout << "hiding factory ui...\n";
            MessageManager::getInstance().sendMessage(new Message(MESSAGE_HIDE_POPUP));
            player->setState(new NothingSelectedState(player));
            break;
    }
}
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
#include "DataMessage.h"
#include "UnitFactory.h"

FactorySelectedState::FactorySelectedState(Player* player, Building* building) : State(player), building(building)
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
        case UI_COMPONENT_CLICKED:
            handleUIEvent(id);
        default:
            std::cout << "hiding factory ui...\n";
            MessageManager::getInstance().sendMessage(new Message(MESSAGE_HIDE_POPUP));
            player->setState(new NothingSelectedState(player));
            break;
    }
}

void FactorySelectedState::handleUIEvent(int id)
{   int value = 0;
    std::string unitScript = "";
    switch (id) {
        case 12:
            std::cout << "create soldier\n";
            unitScript = "unit.lua";
            value = 1000;
            break;
        case 13:
            std::cout << "create tank\n";
            unitScript = "tank.lua";
            value = 3000;
            break;
        case 14:
            std::cout << "create anti_tank\n";
            unitScript = "anti_tank.lua";
            value = 5000;
            break;
        default:
            break;
    }
    //unitScript = unitScript + building->getArmy()->name + ".lua";
    if(foundsAvailable(value)){
        createUnit(unitScript);
    }
}

void FactorySelectedState::createUnit(std::string unitScript)
{
    Player* player = (Player*)model;
    UnitFactory unitFactory;
    Unit* unit = unitFactory.createUnit(unitScript);
    unit->setPosition(building->getTile());
    player->addUnit(unit);
    
    //Sends message to create the view for the unit and attach it to the scene
    DataMessage<Unit*> *message = new DataMessage<Unit*>(MESSAGE_CREATE_UNIT,unit);
    MessageManager::getInstance().sendMessage(message);
}

bool FactorySelectedState::foundsAvailable(int value)
{
    Player* player = (Player*)model;
    bool result = false;
    if (player->getFounds() >= value) {
        player->setFounds(player->getFounds() - value);
        result = true;
    }
    return result;
}
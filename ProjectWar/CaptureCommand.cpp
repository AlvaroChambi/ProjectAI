//
//  CaptureCommand.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 11/4/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#include "CaptureCommand.h"

CaptureCommand::CaptureCommand(Player* player, Unit* unit, Building* building)
                                : player(player), unit(unit), building(building)
{

}

CaptureCommand::~CaptureCommand()
{

}

void CaptureCommand::cancel()
{
    std::cout << "canceling capture commmand\n";
}

void CaptureCommand::execute()
{
    int captureValue = 0;
    std::cout << "executing capture command";
    if (player->getId() == building->getOwnerID()) {
        captureValue = building->getCaptureValue() + unit->getHP();
        
    }else{
        captureValue = unit->getHP();
        building->setOwnerID(player->getId());
    }
    
    building->setCaptureValue(captureValue);
}
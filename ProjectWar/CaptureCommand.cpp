//
//  CaptureCommand.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 11/4/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#include "CaptureCommand.h"

CaptureCommand::CaptureCommand( Player* player, Unit* unit, Building* building )
: player( player ), unit( unit ), building( building ) {
    this->savedCaptureValue = building->getCaptureValue();
    this->savedOwner = building->getOwnerID();
}

CaptureCommand::~CaptureCommand() {

}

bool CaptureCommand::changeContext( MapContext &mapContext ) {
    return false;
}

void CaptureCommand::cancel() {
    building->setOwnerID( savedOwner) ;
    building->setCaptureValue( savedCaptureValue );
}

void CaptureCommand::execute() {
    int captureValue = 0;
    if ( player->getId() == building->getOwnerID() ) {
        captureValue = building->getCaptureValue() + unit->getHP();
        
    }else{
        captureValue = unit->getHP();
        building->setOwnerID(player->getId());
    }
    
    building->setCaptureValue( captureValue );
}
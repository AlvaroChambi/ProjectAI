//
//  CaptureCommand.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 11/4/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#include "CaptureCommand.h"
#include "MapContext.h"

CaptureCommand::CaptureCommand( MapContext& mapContext, const int unitID )
: unitID( unitID ), mapContext( &mapContext ), executed( false ) {
    
}

CaptureCommand::~CaptureCommand() {

}

bool CaptureCommand::changeContext( MapContext& mapContext ) {
    if( !executed ) {
        return true;
    }
    return false;
}

void CaptureCommand::execute() {
    Unit* unit = mapContext->getEntity( unitID );
    Building* building = mapContext->getStructure( unit->getPosition() );
    
    buildingID = building->getId();
    savedOwner = unit->getOwnerID();
    savedCaptureValue = building->getCaptureValue();
    
    int captureValue = 0;
    if ( unit->getOwnerID() == building->getOwnerID() ) {
        captureValue = building->getCaptureValue() + unit->getHP();
    } else {
        captureValue = unit->getHP();
        building->setOwnerID( unit->getOwnerID() );
    }
    
    building->setCaptureValue( captureValue );
}

void CaptureCommand::cancel() {
    Building* building = mapContext->getStructure( buildingID );
    
    building->setOwnerID( savedOwner) ;
    building->setCaptureValue( savedCaptureValue );
}
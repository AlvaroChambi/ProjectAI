//
//  CaptureCommand.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 11/4/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#include "CaptureCommand.h"
#include "MapContext.h"

CaptureCommand::CaptureCommand( const int unitID )
: unitID( unitID ), mapContext( nullptr ) {
    
}

CaptureCommand::~CaptureCommand() {

}

void CaptureCommand::execute( MapContext& context ) {
    if ( mapContext != nullptr ) {
        throw IllegalStateException(
                            "Command state not restored after execution" );
    }
    
    mapContext = &context;
    
    Unit* unit = mapContext->getEntity( unitID );
    Building* building = mapContext->getStructure( unit->getPosition() );
    
    buildingID = building->getId();
    savedOwner = building->getOwnerID();
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
    
    mapContext = nullptr;
}
//
//  BuildingFactory.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 9/6/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#include "BuildingFactory.h"
#include "LuaScript.h"

BuildingFactory::BuildingFactory()
{

}

BuildingFactory::~BuildingFactory()
{

}

Building* BuildingFactory::createBuilding(std::string scriptFile)
{
    Building* building = new Building;
    LuaScript script = LuaScript(scriptFile);
    
    building->setResource(script.get<std::string>("building.resource"));
    building->setCaptureValue(script.get<int>("building.capture_value"));
    building->setType(script.get<std::string>("building.type"));
    
    return building;
}
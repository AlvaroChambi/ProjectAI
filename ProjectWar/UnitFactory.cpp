//
//  UnitFactory.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 2/6/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//
#include "UnitFactory.h"
#include "LuaScript.h"

UnitFactory::UnitFactory()
{

}

UnitFactory::~UnitFactory()
{

}

Unit* UnitFactory::createUnit(std::string scriptFile)
{
    Unit* unit = new Unit;
    LuaScript script(scriptFile);
    unit->setHP(script.get<int>("unit.hp"));
    unit->setMovement(script.get<int>("unit.movement"));
    unit->setResource(script.get<std::string>("unit.resource"));
    unit->setAttackRange(script.get<int>("unit.attack_range"));
    
    //TODO: iterate over the command list to update the available commands
    
    //TODO: map needed to update the unit position
    
    return unit;
}
//
//  Model.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 13/3/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#include "Model.h"

Model::Model() : Observable(), id(0), resource("")
{

}

Model::~Model()
{
    
}

void Model::setid(int id)
{
    this->id = id;
}

int Model::getId()
{
    return id;
}

std::string Model::getResource()
{
    return resource;
}

void Model::setResource( std::string resource )
{
    this->resource = resource;
}
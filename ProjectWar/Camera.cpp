//
//  Camera.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 8/6/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#include "Camera.h"

Camera::Camera() : position(), width(0), height(0)
{
    
}

Camera::Camera(Point position, int width, int height)
    :position(position),
     width(width),
     height(height)
{

}

Camera::~Camera()
{

}


//
//  ResizeCommand.h
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 17/9/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#ifndef __ProjectWar__ResizeCommand__
#define __ProjectWar__ResizeCommand__

#include <stdio.h>
#include "Command.h"

class UIComponent;
class ResizeCommand : public Command
{
public:
    
    ResizeCommand(UIComponent* component, float widthRatio, float heightRatio);
    ~ResizeCommand();
    
    void execute();
    void cancel();
    
    void resize(float widthRatio, float heightRatio);
    
    float widthRatio;
    float heightRatio;
    
    int width;
    int height;
    
    UIComponent* component;
};

#endif /* defined(__ProjectWar__ResizeCommand__) */

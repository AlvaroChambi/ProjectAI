//
//  SDLInputHandler.h
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 12/3/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#ifndef __ProjectWar__SDLInputHandler__
#define __ProjectWar__SDLInputHandler__

#include <stdio.h>
#include "InputHandler.h"
#include <SDL2/SDL.h>

class SDLInputHandler : public InputHandler
{
public:
    SDLInputHandler();
    virtual ~SDLInputHandler();
    void initInputHandler();
    Event* poolEvent();
};

#endif /* defined(__ProjectWar__SDLInputHandler__) */

//
//  SDLInputHandler.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 12/3/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#include "SDLInputHandler.h"
#include <iostream>

SDLInputHandler::SDLInputHandler() : onClickDown(false)
{

}

SDLInputHandler::~SDLInputHandler()
{

}

void SDLInputHandler::initInputHandler()
{

}

Event* SDLInputHandler::poolEvent()
{
    Event* gameEvent = new Event();
    SDL_Event event;
    //TODO Crashing sometimes when polling event (BAD ACCESS)
    while(SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_QUIT:
                gameEvent->type = ON_WINDOW_CLOSED;
                break;
            case SDL_MOUSEMOTION:
                if (onClickDown) {
                    gameEvent->type = ON_MOUSE_DRAG;
                    gameEvent->x = event.motion.x;
                    gameEvent->y = event.motion.y;
                    
                    gameEvent->xRelative = event.motion.xrel;
                    gameEvent->yRelative = event.motion.yrel;
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                gameEvent->type = ON_MOUSE_DOWN_EVENT;
                gameEvent->x = event.motion.x;
                gameEvent->y = event.motion.y;
                this->onClickDown = true;
                break;
            case SDL_MOUSEBUTTONUP:
                this->onClickDown = false;
                break;
            case SDL_KEYDOWN:
                break;
            case SDL_KEYUP:
                break;
            default:
                break;
        }
    }
    return gameEvent;
}

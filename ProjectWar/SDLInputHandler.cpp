//
//  SDLInputHandler.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 12/3/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#include "SDLInputHandler.h"

SDLInputHandler::SDLInputHandler()
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
    while(SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_QUIT:
                gameEvent->type = ON_WINDOW_CLOSED;
                break;
            case SDL_MOUSEMOTION:
                break;
            case SDL_MOUSEBUTTONDOWN:
                gameEvent->type = ON_MOUSE_DOWN_EVENT;
                gameEvent->x = event.motion.x;
                gameEvent->y = event.motion.y;
                break;
            case SDL_MOUSEBUTTONUP:
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

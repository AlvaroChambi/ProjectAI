#include <iostream>

#include <SDL2/SDL.h>
#include "Game.h"

const int FPS = 60;
const int DELAY_TIME = 1000.0f / FPS;

int main(int argc, char * arg[])
{
    Uint32 frameStart, frameTime;
    Game game = Game();
    
    game.onInit();
    
    while(game.isRunning()){
        frameStart = SDL_GetTicks();
        
        game.onProcessInput();
        game.onUpdate();
        game.onRender();
        
        frameTime = SDL_GetTicks() - frameStart;
        
        if(frameTime < DELAY_TIME){
           SDL_Delay(DELAY_TIME - frameTime);
            SDL_Delay(DELAY_TIME - frameTime);
        }
    }
    
    game.onFinish();
    
    return 0;
}
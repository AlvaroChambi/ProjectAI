#include <stdio.h>

#ifdef __APPLE__
#include <SDL2/SDL.h>
#else
#include <SDL.h>
#endif
#include "Game.h"

const int FPS = 30;
const int DELAY_TIME = 1000.0f / FPS;

int main(int argc, char* arg[]) {
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
        }
    }
    
    game.onFinish();
    
    return 0;
}
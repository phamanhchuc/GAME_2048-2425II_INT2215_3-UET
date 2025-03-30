#include "game.h"
#include <SDL2/SDL.h>

using namespace std;

int main(int argc, char* args[]) {
    Game game;
    if (!game.init()) {
        SDL_Log("Failed to initialize the game.");
        return -1;
    }

    game.run(); 
    return 0;
}

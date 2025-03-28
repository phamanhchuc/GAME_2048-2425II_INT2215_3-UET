#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <string>
#include "board.h"
#include "texture.h"

using namespace std;

enum GameState {
    PLAYING,
    WON,
    GAME_OVER
};

class Game {
public:
    Game();
    ~Game();

    bool init();
    void run();
    void close();

private:
    void handleEvents(SDL_Event& e);
    void update();
    void render();
    void renderEndMessage(const string& msg);
    void reset();

    SDL_Window* window;
    SDL_Renderer* renderer;
    TTF_Font* font;
    Mix_Chunk* moveSound;
    Mix_Chunk* winSound;
    Mix_Chunk* loseSound;

    Texture tileTextures[12];
    Board board;

    bool quit;
    GameState state;
};

#endif

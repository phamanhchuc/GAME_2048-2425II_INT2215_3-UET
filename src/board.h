#ifndef BOARD_H
#define BOARD_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include "texture.h"

class Board {
public:
    Board();
    Board(Texture* tiles, TTF_Font* font, SDL_Renderer* renderer, Mix_Chunk* moveSound);

    void handleInput(SDL_Keycode key);
    void render();
    void cleanUp();
    void reset();            // 🆕 Hàm reset game
    int getScore() const;    // 🆕 Hàm lấy điểm hiện tại

public:
    int grid[4][4];
    int score;               // 🆕 Biến lưu điểm số

    Texture* tileTextures;
    TTF_Font* font;
    SDL_Renderer* renderer;
    Mix_Chunk* moveSound;

    void spawnTile();
    bool moveLeft();
    bool moveRight();
    bool moveUp();
    bool moveDown();
    bool canMove();
    void drawTile(int val, int x, int y);
};

#endif

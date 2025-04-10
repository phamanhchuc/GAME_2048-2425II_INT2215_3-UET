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

    void handleInput(SDL_Keycode key); // Xử lý thao tác di chuyển của user
    void render();
    void cleanUp();
    void reset();       
    void loadHighScore();    // Đọc từ file
    void saveHighScore();    // Ghi vào file 
    int getHighScore() const;    
    int getScore() const;   

public:
    int grid[4][4];
    int score;   
    int highScore;            

    Texture* tileTextures;
    TTF_Font* font;
    SDL_Renderer* renderer;
    Mix_Chunk* moveSound;

    void spawnTile(); // Sinh ô số mới sau mỗi lượt đi.
    bool moveLeft();
    bool moveRight();
    bool moveUp();
    bool moveDown();
    bool canMove(); //  Kiểm tra xem còn nước đi hợp lệ không.
    void drawTile(int val, int x, int y);
};

#endif

#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <string>
#include "board.h" 
#include "texture.h" // Xử lý hình ảnh

using namespace std;

// Trạng thái của trò chơi
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
    void handleEvents(SDL_Event& e); // Xử lý sự kiện người dùng
    void update(); // Cập nhật trạng thái trò chơi
    void render(); // Vẽ giao diện trò chơi
    void renderEndMessage(const string& msg); // Hiển thị thông báo khi thắng/thua
    void reset(); // Đặt lại trò chơi khi bắt đầu lại

    SDL_Window* window;
    SDL_Renderer* renderer;
    TTF_Font* font; 
    Mix_Chunk* moveSound;
    Mix_Chunk* winSound;
    Mix_Chunk* loseSound;

    Texture tileTextures[12];
    Texture bgTexture; 
    Board board;

    bool quit; // Cờ để kiểm tra khi nào thoát trò chơi
    GameState state;
};

#endif

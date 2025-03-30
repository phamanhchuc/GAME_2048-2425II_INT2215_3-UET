#include "game.h"
#include <SDL2/SDL.h>

using namespace std;

int main(int argc, char* args[]) {
    Game game;
    
    // Kiểm tra nếu game không khởi tạo thành công, in lỗi và thoát
    if (!game.init()) {
        SDL_Log("Failed to initialize the game.");
        return -1;
    }

    game.run(); // Chạy vòng lặp chính của trò chơi
    return 0;
}

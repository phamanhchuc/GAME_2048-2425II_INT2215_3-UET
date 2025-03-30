#include "game.h"
#include <iostream>

using namespace std;

Game::Game()
    : window(nullptr), renderer(nullptr), font(nullptr),
      moveSound(nullptr), winSound(nullptr), loseSound(nullptr),
      quit(false), state(PLAYING) {}

Game::~Game() { close(); }

bool Game::init() {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) return false;
    if (TTF_Init() == -1) return false;

    // Tạo cửa sổ trò chơi
    window = SDL_CreateWindow("2048", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 400, 450, SDL_WINDOW_SHOWN);
    if (!window) return false;

    // Tạo renderer để vẽ đồ họa
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) return false;

    // Load font 
    font = TTF_OpenFont("assets/Boldonse-Regular.ttf", 24);
    if (!font) return false;

     // Khởi tạo âm thanh
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    moveSound = Mix_LoadWAV("assets/music/music.wav");
    winSound = Mix_LoadWAV("assets/music/winmusic.wav");
    loseSound = Mix_LoadWAV("assets/music/losemusic.wav");

    // Load tile textures
    string tilePathPrefix = "assets/image/numbers/";
    for (int i = 0, val = 2; i < 12; ++i, val *= 2) {
        string path = tilePathPrefix + to_string(val) + ".png";
        tileTextures[i].loadFromFile(path, renderer);
    }

    // Khởi tạo bàn cờ
    board = Board(tileTextures, font, renderer, moveSound);

    // Load background
    bgTexture.loadFromFile("/Users/stonyyquynh/Desktop/2048 Game/assets/image/background.png", renderer);
    if (!bgTexture.loadFromFile("assets/image/background.png", renderer)) {
        cout << "Failed to load background texture!" << endl;
        return false;
    }
    
    return true;
}

void Game::run() {
    SDL_Event e;
    while (!quit) {
        while (SDL_PollEvent(&e)) {
            handleEvents(e);
        }
        update();
        render();
        SDL_Delay(16); // tránh quá nhanh
    }
}

void Game::handleEvents(SDL_Event& e) {
    if (e.type == SDL_QUIT) {
        quit = true;
    } else if (e.type == SDL_KEYDOWN) {
        if (state == PLAYING) {
            switch (e.key.keysym.sym) {
                case SDLK_ESCAPE:
                    quit = true;
                    break;
                default:
                    board.handleInput(e.key.keysym.sym);
                    break;
            }
        } else {
            if (e.key.keysym.sym == SDLK_RETURN) {
                reset();  // Nhấn Enter để chơi lại
            }
        }
    }
}

void Game::update() {
    if (state == PLAYING) {
        // Check thắng
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j)
                if (board.grid[i][j] == 2048) {
                    state = WON;
                    Mix_PlayChannel(-1, winSound, 0);
                }

        // Check thua
        if (!board.canMove()) {
            state = GAME_OVER;
            Mix_PlayChannel(-1, loseSound, 0);
        }
    }
}

void Game::render() {
    SDL_SetRenderDrawColor(renderer, 250, 248, 239, 255);
    SDL_RenderClear(renderer);

    // Hiển thị background
    SDL_Rect fullScreen = {0, 0, 400, 450};  // Điều chỉnh kích thước nếu cần
    SDL_RenderCopy(renderer, bgTexture.getTexture(), nullptr, &fullScreen);

    board.render();

    if (state == WON) {
        renderEndMessage("You Win! Press Enter");
    } else if (state == GAME_OVER) {
        renderEndMessage("Game Over! Press Enter");
    }

    SDL_RenderPresent(renderer);
}


void Game::renderEndMessage(const string& msg) {
    SDL_Color color = { 119, 110, 101 };
    Texture text;
    text.loadFromText(renderer, font, msg, color);

    int x = (400 - text.getWidth()) / 2;
    int y = 170;

    text.render(x, y);
}

void Game::reset() {
    board = Board(tileTextures, font, renderer, moveSound);
    state = PLAYING;
}

void Game::close() {
    board.cleanUp();

    for (int i = 0; i < 12; ++i) tileTextures[i].free();
    
    bgTexture.free();  // Giải phóng background

    if (moveSound) Mix_FreeChunk(moveSound);
    if (winSound) Mix_FreeChunk(winSound);
    if (loseSound) Mix_FreeChunk(loseSound);
    if (font) TTF_CloseFont(font);
    if (renderer) SDL_DestroyRenderer(renderer);
    if (window) SDL_DestroyWindow(window);

    Mix_Quit();
    TTF_Quit();
    SDL_Quit();
}

#include "board.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <cstring>

using namespace std;

Board::Board() {}

Board::Board(Texture* tiles, TTF_Font* font, SDL_Renderer* renderer, Mix_Chunk* moveSound)
    : grid{{0}}, score(0), tileTextures(tiles), font(font), renderer(renderer), moveSound(moveSound) {
    srand(static_cast<unsigned>(time(nullptr)));
    spawnTile();
    spawnTile();
}

void Board::spawnTile() {
    int empty[16][2];
    int count = 0;
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            if (grid[i][j] == 0)
                empty[count][0] = i, empty[count++][1] = j;

    if (count > 0) {
        int r = rand() % count;
        int i = empty[r][0], j = empty[r][1];
        grid[i][j] = (rand() % 10 == 0) ? 4 : 2;
    }
}

void Board::handleInput(SDL_Keycode key) {
    bool moved = false;
    switch (key) {
        case SDLK_LEFT:  moved = moveLeft();  break;
        case SDLK_RIGHT: moved = moveRight(); break;
        case SDLK_UP:    moved = moveUp();    break;
        case SDLK_DOWN:  moved = moveDown();  break;
    }
    if (moved) {
        Mix_PlayChannel(-1, moveSound, 0);
        spawnTile();
    }
}

void Board::render() {
    SDL_SetRenderDrawColor(renderer, 250, 248, 239, 255); // nền
    SDL_RenderClear(renderer);

    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            drawTile(grid[i][j], j * 100, i * 100);

    // Vẽ điểm
    SDL_Color color = { 119, 110, 101 };
    string scoreText = "Score: " + to_string(score);
    SDL_Surface* surface = TTF_RenderText_Blended(font, scoreText.c_str(), color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_Rect dst = { 10, 410, surface->w, surface->h }; // cần đảm bảo cửa sổ cao > 400
    SDL_RenderCopy(renderer, texture, NULL, &dst);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

void Board::drawTile(int val, int x, int y) {
    SDL_Rect dst = { x + 5, y + 5, 90, 90 };
    if (val == 0) {
        SDL_SetRenderDrawColor(renderer, 205, 193, 180, 255);
        SDL_RenderFillRect(renderer, &dst);
    } else {
        int index = 0, temp = val;
        while (temp > 2) {
            temp /= 2;
            ++index;
        }
        if (tileTextures[index].isLoaded()) {
            tileTextures[index].render(x + 5, y + 5);
        }
    }
}

bool Board::moveLeft() {
    bool moved = false;
    for (int i = 0; i < 4; ++i) {
        int lastMerge = -1;
        for (int j = 1; j < 4; ++j) {
            if (grid[i][j] == 0) continue;
            int k = j;
            while (k > 0 && grid[i][k - 1] == 0) {
                grid[i][k - 1] = grid[i][k];
                grid[i][k] = 0;
                --k;
                moved = true;
            }
            if (k > 0 && grid[i][k - 1] == grid[i][k] && lastMerge != k - 1) {
                grid[i][k - 1] *= 2;
                score += grid[i][k - 1];
                grid[i][k] = 0;
                lastMerge = k - 1;
                moved = true;
            }
        }
    }
    return moved;
}

bool Board::moveRight() {
    bool moved = false;
    for (int i = 0; i < 4; ++i) {
        int lastMerge = 4;
        for (int j = 2; j >= 0; --j) {
            if (grid[i][j] == 0) continue;
            int k = j;
            while (k < 3 && grid[i][k + 1] == 0) {
                grid[i][k + 1] = grid[i][k];
                grid[i][k] = 0;
                ++k;
                moved = true;
            }
            if (k < 3 && grid[i][k + 1] == grid[i][k] && lastMerge != k + 1) {
                grid[i][k + 1] *= 2;
                score += grid[i][k + 1];
                grid[i][k] = 0;
                lastMerge = k + 1;
                moved = true;
            }
        }
    }
    return moved;
}

bool Board::moveUp() {
    bool moved = false;
    for (int j = 0; j < 4; ++j) {
        int lastMerge = -1;
        for (int i = 1; i < 4; ++i) {
            if (grid[i][j] == 0) continue;
            int k = i;
            while (k > 0 && grid[k - 1][j] == 0) {
                grid[k - 1][j] = grid[k][j];
                grid[k][j] = 0;
                --k;
                moved = true;
            }
            if (k > 0 && grid[k - 1][j] == grid[k][j] && lastMerge != k - 1) {
                grid[k - 1][j] *= 2;
                score += grid[k - 1][j];
                grid[k][j] = 0;
                lastMerge = k - 1;
                moved = true;
            }
        }
    }
    return moved;
}

bool Board::moveDown() {
    bool moved = false;
    for (int j = 0; j < 4; ++j) {
        int lastMerge = 4;
        for (int i = 2; i >= 0; --i) {
            if (grid[i][j] == 0) continue;
            int k = i;
            while (k < 3 && grid[k + 1][j] == 0) {
                grid[k + 1][j] = grid[k][j];
                grid[k][j] = 0;
                ++k;
                moved = true;
            }
            if (k < 3 && grid[k + 1][j] == grid[k][j] && lastMerge != k + 1) {
                grid[k + 1][j] *= 2;
                score += grid[k + 1][j];
                grid[k][j] = 0;
                lastMerge = k + 1;
                moved = true;
            }
        }
    }
    return moved;
}

bool Board::canMove() {
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            if (grid[i][j] == 0)
                return true;

    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 3; ++j)
            if (grid[i][j] == grid[i][j + 1] || grid[j][i] == grid[j + 1][i])
                return true;

    return false;
}

void Board::reset() {
    memset(grid, 0, sizeof(grid));
    score = 0;
    spawnTile();
    spawnTile();
}

int Board::getScore() const {
    return score;
}

void Board::cleanUp() {
    tileTextures = nullptr;
    font = nullptr;
    renderer = nullptr;
    moveSound = nullptr;
}

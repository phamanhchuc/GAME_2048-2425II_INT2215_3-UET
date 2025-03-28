#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>

class Texture {
public:
    Texture();
    ~Texture();

    bool loadFromFile(const std::string& path, SDL_Renderer* renderer); // Cách 2
    bool loadFromText(SDL_Renderer* renderer, TTF_Font* font, const std::string& text, SDL_Color color); // 👉 Thêm cái này

    void render(int x, int y);
    void free();
    bool isLoaded() const;

    int getWidth() const { return width; }
    int getHeight() const { return height; }

private:
    SDL_Texture* texture;
    SDL_Renderer* renderer;
    int width, height;
};

#endif

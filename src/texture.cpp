#include "texture.h"

Texture::Texture() : texture(nullptr), renderer(nullptr), width(0), height(0) {}

Texture::~Texture() {
    free();
}

// Load texture từ file ảnh
bool Texture::loadFromFile(const std::string& path, SDL_Renderer* renderer) {
    free();
    this->renderer = renderer;

    SDL_Surface* loaded = IMG_Load(path.c_str());
    if (!loaded) return false;

    texture = SDL_CreateTextureFromSurface(renderer, loaded);
    width = loaded->w;
    height = loaded->h;
    SDL_FreeSurface(loaded);

    return texture != nullptr;
}

// // Load texture từ văn bản
bool Texture::loadFromText(SDL_Renderer* renderer, TTF_Font* font, const std::string& text, SDL_Color color) {
    free();
    this->renderer = renderer;

    SDL_Surface* textSurface = TTF_RenderText_Blended(font, text.c_str(), color);
    if (!textSurface) return false;

    texture = SDL_CreateTextureFromSurface(renderer, textSurface);
    width = textSurface->w;
    height = textSurface->h;
    SDL_FreeSurface(textSurface);

    return texture != nullptr;
}

void Texture::render(int x, int y) {
    if (!texture || !renderer) return;

    SDL_Rect dst = { x, y, width, height };
    SDL_RenderCopy(renderer, texture, nullptr, &dst);
}

void Texture::free() {
    if (texture) {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }
    width = height = 0;
}

bool Texture::isLoaded() const {
    return texture != nullptr;
}

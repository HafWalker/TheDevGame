#include "stdafx.h"
#include "TextureManager.h"

sf::RenderWindow* window = nullptr;

void TextureManager::SetRenderTarget(sf::RenderWindow* win) {
    window = win;
}

sf::Texture* TextureManager::LoadTexture(const char* fileName) {
    sf::Texture* texture = new sf::Texture();
    if (texture->loadFromFile(fileName)) {
        return texture;
    }
    else {
        return nullptr;
    }
}

void TextureManager::Draw(sf::Sprite& sprite) {
    window->draw(sprite);
}
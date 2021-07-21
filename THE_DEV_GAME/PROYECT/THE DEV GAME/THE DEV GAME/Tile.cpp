#include "stdafx.h"
#include "Tile.h"

//Tile::Tile(sf::Texture& texture_sheet, sf::IntRect texture_rect, bool damaging) : damaging(damaging){
//    this->sprite.setTexture(texture_sheet);
//    this->sprite.setTextureRect(texture_rect);
//}

Tile::Tile() {
}

Tile::Tile(float x, float y, float gridSizeF, int layer) {
    this->shape.setSize(sf::Vector2f(gridSizeF, gridSizeF));

    if (layer == 0) {
        this->shape.setFillColor(sf::Color::Red);
    }
    else if (layer == 1) {
        this->shape.setFillColor(sf::Color::Green);
    }

    this->shape.setOutlineThickness(1.f);
    this->shape.setOutlineColor(sf::Color::Black);
    this->shape.setPosition(x,y);
}

Tile::~Tile() {
}

const sf::FloatRect Tile::getGlobalbBounds() const {
    return this->sprite.getGlobalBounds();
}

void Tile::update() {
}

void Tile::render(sf::RenderTarget& target) {
    target.draw(this->shape);
}



#include "stdafx.h"
#include "TileMap.h"

TileMap::TileMap() {
	// Initialize tilemap
	std::cout << "Init tilemap" << "\n";
	this->gridSizeF = 50.f;
	this->gridSizeU = static_cast<unsigned>(this->gridSizeF);
	this->maxSize.x = 16;
	this->maxSize.y = 12;
	this->layers = 1;

	this->map.resize(this->maxSize.x);
	for (size_t x = 0; x < this->maxSize.x; x++) {
		this->map.push_back(std::vector<std::vector<Tile>>());
		for (size_t y = 0; y < this->maxSize.y; y++) {
			this->map[x].push_back(std::vector<Tile>());
			for (size_t z = 0; z < this->layers; z++) {
				this->map[x][y].resize(this->layers);

				if (y == this->maxSize.y - 1) {
					this->map[x][y].push_back(Tile(x * this->gridSizeF, y * this->gridSizeF, this->gridSizeF, 1));
				}
				else {
					this->map[x][y].push_back(Tile(x * this->gridSizeF, y * this->gridSizeF, this->gridSizeF, 0));
				}
			}
		}
	}
}

TileMap::~TileMap() {
}

void TileMap::addTile(unsigned x, unsigned y) {
}

void TileMap::removeTile(unsigned x, unsigned y) {
}

void TileMap::update() {
}

void TileMap::render(sf::RenderTarget & target) {
	for (auto &x : this->map) {
		for (auto &y : x) {
			for (auto& z : y) {
				z.render(target);
			}
		}
	}
}

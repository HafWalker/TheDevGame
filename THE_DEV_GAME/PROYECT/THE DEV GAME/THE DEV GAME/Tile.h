#pragma once
class Tile
{
private:
	sf::Sprite sprite;
	//const bool damaging;
protected:
	sf::RectangleShape shape;
public:
	Tile();
	Tile(float x, float y, float gridSizeF, int layer); //sf::Texture& texture_sheet, sf::IntRect texture_rect, bool damaging = false);
	virtual ~Tile();
	
	const sf::FloatRect getGlobalbBounds() const;

	void update();
	void render(sf::RenderTarget& target);
};


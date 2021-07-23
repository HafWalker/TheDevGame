#include "stdafx.h"
#include "Game.h"

int main() {
	
	srand(static_cast<unsigned>(time(0)));
	
	Game game;
	
	while (game.getWindow().isOpen()) {
		game.updateDeltaTime();
		game.update();
		game.render();
	}

	std::cout << "EndGame" << std::endl;
	//End of application
	return 0;
}
#include "stdafx.h"
#include "Game.h"

int main() {
	
	srand(static_cast<unsigned>(time(0)));
	
	Game game;
	
	game.run();

	std::cout << "EndGame" << std::endl;
	//End of application
	return 0;
}
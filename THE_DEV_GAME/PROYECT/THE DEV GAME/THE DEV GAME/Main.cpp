#include "stdafx.h"
#include "Game.h"

static bool Compare(pair<int, string>& a, pair<int, string>& b) {
	bool result = a.first > b.first;
	return result;
}

int main() {
	
	srand(static_cast<unsigned>(time(0)));
	
	Game game;
	
	game.run();

	std::cout << "EndGame" << std::endl;
	//End of application
	return 0;
}
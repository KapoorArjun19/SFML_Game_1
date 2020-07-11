#include "Game.h"

int main() {

	std::srand(static_cast<unsigned>(time(NULL)));

	Game game;

	//Game Loop
	while (game.running() && !game.getEndGame())
	{
		//Update
		game.update();

		//Render
		game.render();
	}
}